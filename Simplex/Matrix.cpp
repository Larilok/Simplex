#include "Matrix.h"
#include <msclr\marshal_cppstd.h>

#define ZERO Fraction(Bignum("0"), Bignum("1"))

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

Fraction Matrix::getElement(int row, int column)
{
	return data[row][column];
}

std::size_t Matrix::getLength() const
{
	return data[0].size();
}

std::size_t Matrix::getHeight() const
{
	return data.size();
}

Fraction Matrix::getEquivalent(int row)
{
	return data[row][getLength()-1];
}


void Matrix::Str2CharPtr(System::String^ str, std::string& standardString)
{
	// Pin memory so GC can't move it while native function is called
	msclr::interop::marshal_context context;
	standardString = context.marshal_as<std::string>(str);
	if (standardString == "") standardString = "0";
}

void Matrix::insert_nonbasic_variable_simplex(
	std::vector<size_t>& variables,
	std::vector<size_t>& basis,
	Var type, std::string value, size_t &current_row)
{
	variables.push_back(type);
	if(value == "1") basis.push_back(variables.size() - 1);

	for (size_t k = 0; k < getHeight(); k++)
	{
		if (k == current_row+1) data[k].push_back(Fraction(Bignum(value), Bignum("1")));
		else data[k].push_back(ZERO);
	}
}




Matrix::Matrix(System::Windows::Forms::DataGridView^ restrictions_table,
	System::Windows::Forms::DataGridView^ targetFunction,
	std::vector<size_t>& variables,
	std::vector<size_t>& basis): 
		data(restrictions_table->RowCount+1, std::vector<Fraction>(targetFunction->ColumnCount-1))
{
	std::string buffer;	//buffer to save value from input
	size_t found; //if input is "a/b" saves '/' position

	//fills first row with values of targerFunction
	for (std::size_t i = 0; i < targetFunction->ColumnCount-1; i++)	{
		Str2CharPtr(System::Convert::ToString(targetFunction->Rows[0]->Cells[i]->Value), buffer);
		found = buffer.find('/');
		if (found != std::string::npos) data[0][i] = Fraction(-Bignum(buffer.substr(0, found)), Bignum(buffer.substr(found+1)));
		else data[0][i] = Fraction(-Bignum(buffer), Bignum("1"));
		variables.push_back(Var::Basic);
	}
	//fills rest of table
	for (std::size_t i = 0; i < restrictions_table->RowCount; i++) {
		//add basic variables
		for (std::size_t j = 0; j < restrictions_table->ColumnCount-2; j++) {
			Str2CharPtr(System::Convert::ToString(restrictions_table->Rows[i]->Cells[j]->Value), buffer);
			found = buffer.find('/');
			if (found != std::string::npos) data[i+1][i] = Fraction(-Bignum(buffer.substr(0, found)), Bignum(buffer.substr(found + 1)));
			else data[i+1][j] = Fraction(Bignum(buffer), Bignum("1"));
		}
		//process comparer cell
		 Str2CharPtr(System::Convert::ToString(
			 restrictions_table->Rows[i]->Cells[restrictions_table->ColumnCount - 2]->Value), buffer);
		if (buffer == "<=") {
			insert_nonbasic_variable_simplex(variables, basis, Var::Slack, "1", i);
		}
		else if (buffer == ">=") {
			insert_nonbasic_variable_simplex(variables, basis, Var::Slack, "-1", i);
			insert_nonbasic_variable_simplex(variables, basis, Var::Surplus, "1", i);
		}
		else {
			insert_nonbasic_variable_simplex(variables, basis, Var::Surplus, "1", i);
		}
	}
	//add b cell
	for (std::size_t i = 0; i < restrictions_table->RowCount; i++) {
		Str2CharPtr(System::Convert::ToString(restrictions_table->Rows[i]->Cells[restrictions_table->ColumnCount - 1]->Value), buffer);
		found = buffer.find('/');
		if (found != std::string::npos) data[i + 1].push_back(Fraction(-Bignum(buffer.substr(0, found)), Bignum(buffer.substr(found + 1))));
		else data[i + 1].push_back(Fraction(Bignum(buffer), Bignum("1")));
	}
	// add C target function
	Str2CharPtr(System::Convert::ToString(targetFunction->Rows[0]->Cells[targetFunction->ColumnCount - 1]->Value), buffer);
	found = buffer.find('/');
	if (found != std::string::npos) data[0].push_back(Fraction(-Bignum(buffer.substr(0, found)), Bignum(buffer.substr(found + 1))));
	else data[0].push_back(Fraction(Bignum(buffer), Bignum("1")));
}

Matrix::Matrix() : Matrix(1, 1) {}

Matrix::Matrix(const int& c, const int& r) : data(r, std::vector<Fraction>(c, ZERO)){}

Matrix::Matrix(const Matrix& M)
{
	data = std::vector<std::vector<Fraction>>(getHeight(), std::vector<Fraction>(getLength()));
	for (int i = 0; i < getHeight(); i++) {
		for (int j = 0; j < getLength(); j++)
			data[i][j] = M.data[i][j];
	}
}

Matrix::~Matrix()
{ }




void Matrix::swapRows(int& r1, int& r2)
{
	Fraction temp;
	for (int i = 0; i < getLength(); i++)
	{
		temp = data[r1][i];
		data[r1][i] = data[r2][i];
		data[r2][i] = temp;
	}
}

void Matrix::deleteSurplusColumn(std::size_t c)
{
	for (size_t i = 0; i < getHeight(); i++)
	{
		data[i].erase(data[i].begin() + c);
	}
}

void Matrix::simplex_solution(std::ostream& logs, const bool& min_max, std::vector<size_t>& variables, std::vector<size_t>& basis_indexes)
{
	printSimplexMatrix(logs,*this, variables, basis_indexes);
	//STAGE 1
	logs << "STAGE 1\nNew target function will be `min r = Surplus(1) + Surplas(2)...` and original will be the second row" <<std::endl <<std::endl;
	data.insert(data.begin(), std::vector<Fraction>(getLength(), ZERO));
	for (size_t i = 0; i < getLength(); i++)
	{
		if (i != variables.size()) {
			if (variables[i] == Var::Surplus) continue;
		}
		for (size_t j = 2; j < getHeight(); j++)
		{
			if (variables[basis_indexes[j - 2]] == Var::Surplus)
				data[0][i] = data[0][i] + data[j][i];
		}
	}
	printSimplexMatrix(logs, *this, variables, basis_indexes);

	int i, j, r;
	int column_new_basic_variable, row_basic_var_to_be_del;

	for (i = 0; true; i++)
	{
		column_new_basic_variable = maxMinIndexInRow(0, false);
		if (data[0][column_new_basic_variable] <= ZERO) break; //mininimized

		row_basic_var_to_be_del = minRatioIndexInColumn(column_new_basic_variable, 2);
		if (row_basic_var_to_be_del < 0) {
			logs << "All ratios for unoptimal value in column "
				<< column_new_basic_variable + 1
				<< " are < 0\nUnbound!!!\nPlease check your input"
				<< std::endl << std::endl;
			printSimplexMatrix(logs, *this, variables, basis_indexes);
			return;  //completelly wrong
		}

		logs << column_new_basic_variable+1 << "+, " << basis_indexes[row_basic_var_to_be_del - 2]+1 << "-" << std::endl << std::endl;
		//delete Surplus var to speed up calculation
		if (variables[basis_indexes[row_basic_var_to_be_del - 2]] == Var::Surplus) {
			logs << "Delete surplus variable to speed up calculations at index "
				<< basis_indexes[row_basic_var_to_be_del - 2] << std::endl << std::endl;
			variables.erase(variables.begin() + basis_indexes[row_basic_var_to_be_del - 2]);
			for (size_t& var : basis_indexes)
			{
				if (var > basis_indexes[row_basic_var_to_be_del - 2]) var--;
			}
			deleteSurplusColumn(basis_indexes[row_basic_var_to_be_del - 2]);
		}
		basis_indexes[row_basic_var_to_be_del - 2] = column_new_basic_variable;

		JordanGauss_rotation(column_new_basic_variable, row_basic_var_to_be_del);
		printSimplexMatrix(logs, *this, variables, basis_indexes);
	}

	if (data[0][getLength() - 1] > ZERO) {
		logs << "Min r result is optimal, but `> 0`. Surplas variables are still in basis.\nNO SOLUTION\n\n";
		printSimplexMatrix(logs, *this, variables, basis_indexes);
		return;
	}

	//delete stage 1 target function
	data.erase(data.begin());

	logs << "STAGE 2" << std::endl << std::endl;
	//STAGE 2
	printSimplexMatrix(logs, *this, variables, basis_indexes);
	for (size_t i = 0; true; i++)
	{
		column_new_basic_variable = maxMinIndexInRow(0, min_max);

		if (min_max) {
			if (data[0][column_new_basic_variable] >= ZERO) //maximized
				break;
		}
		else {
			if (data[0][column_new_basic_variable] <= ZERO) //minimized
				break;
		}
		
		row_basic_var_to_be_del = minRatioIndexInColumn(column_new_basic_variable, 1);
		if (row_basic_var_to_be_del < 0) {
			logs << "All ratios for unoptimal value in column " 
				<< column_new_basic_variable + 1 
				<< " are < 0\nUnbound!!!\nPlease check your input"
				<< std::endl << std::endl;
			printSimplexMatrix(logs, *this, variables, basis_indexes);
			return;  //completelly wrong
		}
		logs << column_new_basic_variable+1 << "+, " << basis_indexes[row_basic_var_to_be_del - 1]+1 << "-" << std::endl << std::endl;
		basis_indexes[row_basic_var_to_be_del - 1] = column_new_basic_variable;

		JordanGauss_rotation(column_new_basic_variable, row_basic_var_to_be_del);
		printSimplexMatrix(logs, *this, variables, basis_indexes);
	}

	//check for multiple answer if targetFunction || one of the restrictions
	for (size_t i = 0; i < getLength(); i++)
	{
		//one of non-basis vars should be = 0 in solution in targetFunction
		if (data[0][i] == ZERO) {
			bool is_present = false;
			for (size_t j = 0; j < basis_indexes.size(); j++) {
				if (basis_indexes[j] == i) is_present = true;
			}
			if (is_present) continue;
			logs << "Multiple optimal solution 'cos one of non-basis vars is 0" << std::endl << "Finding another edge point of the vector-solution" << std::endl << std::endl;
			column_new_basic_variable = i;
			//add this variable to basis to find another edge point of the vector-solution
			row_basic_var_to_be_del = minRatioIndexInColumn(column_new_basic_variable, 1);
			if (row_basic_var_to_be_del < 0) {
				logs << "All ratios for unoptimal value in column "
					<< column_new_basic_variable + 1
					<< " are < 0\nUnbound!!!\nPlease check your input"
					<< std::endl << std::endl;
				printSimplexMatrix(logs, *this, variables, basis_indexes);
				return;  //completelly wrong
			}
			logs << column_new_basic_variable+1 << "+, " << basis_indexes[row_basic_var_to_be_del - 1]+1 << "-" << std::endl << std::endl;
			basis_indexes[row_basic_var_to_be_del - 1] = column_new_basic_variable;

			JordanGauss_rotation(column_new_basic_variable, row_basic_var_to_be_del);
			printSimplexMatrix(logs, *this, variables, basis_indexes);
			break;
		}
	}
	
}

int Matrix::minRatioIndexInColumn(int c, int restrictions_start_row)
{
	int row_index = -1;
	Fraction ratio;
	for (int i = restrictions_start_row; i < getHeight(); ++i) {
		try {
			if (row_index == -1) {
				ratio = data[i][getLength() - 1] / data[i][c];
				if (ratio < ZERO) continue;
				row_index = i;
			}
			else {
				Fraction temp = data[i][getLength() - 1] / data[i][c];
				if (temp < ZERO) continue;
				if (ratio > temp) {
					ratio = temp;
					row_index = i;
				}
			}
		}
		catch (std::exception e) {
			continue;
		}
	}
	return row_index;
}

int Matrix::maxMinIndexInRow(int r, const bool min_max)
{
	int column_index = 0;
	if (min_max == false) {
		for (int i = 1; i < getLength() - 1; ++i)
			if (data[r][i] > data[r][column_index])        //selecting max in a row
				column_index = i;
	}
	if (min_max == true) {
		for (int i = 1; i < getLength() - 1; ++i)
			if (data[r][column_index] > data[r][i])        //selecting min in a row
				column_index = i;
	}
	return column_index;
}

void Matrix::JordanGauss_rotation(size_t column_new_basic_variable, size_t row_basic_var_to_be_del)
{
	size_t i, j, r;
	// make pivot = 1 by dividing all elements of the row
	Fraction pivot = data[row_basic_var_to_be_del][column_new_basic_variable];
	for (size_t j = 0, r = row_basic_var_to_be_del; j < getLength(); ++j) {
		data[r][j] = data[r][j] / pivot;
	}
	// Jorge-gauss
	Fraction div;
	for (i = 0; i < getHeight(); ++i) {
		if (i != row_basic_var_to_be_del) {
			div = data[i][column_new_basic_variable];
			for (j = 0; j < getLength(); ++j)
				data[i][j] = data[i][j] - (div * data[row_basic_var_to_be_del][j]);
		}
	}
}

int Matrix::backIter(std::vector<size_t>& where, std::vector<Fraction>& answer) {

	int r = getHeight() - 1, k = getLength() - 1, i, j;

	while (k >= 0 && r >= 0) {
		if (where[r] != -1) {
			answer[k] = data[r][getLength()-1] / data[where[r]][k];	//diagonal elem(k) / b(k)

			for (i = k + 1; i < getLength(); i++)
				answer[k] -= data[k][i] * answer[i] / data[k][k];  //insert x and solve
		}
		else if (data[k][getLength()-1])throw std::exception("Error!\ndet = 0");
		k--, r--;
	}
	for (i = 0; i < getHeight(); ++i) {       //checking is answer take a place at all
		Fraction sum;
		for (j = 0; j < getLength(); ++j)
			sum += answer[j] * data[i][j];     //solving left part

		if (Fraction::abs(sum - data[i][getLength()-1]) > ZERO)            //something went complitely wrong
			return 0;

	}

	return 1;

}

std::ostream& Matrix::printSimplexMatrix(std::ostream& out, const Matrix& M, const std::vector<size_t>& variables, const std::vector<size_t>& basis_indexes)
{
	size_t columnWidth = 8;
	//print head
	for (size_t i = 0; i < columnWidth; i++) { out << " "; }

	for (size_t i = 0, b = 1, s = 1; i < variables.size(); i++)
	{
		if (variables[i] == Var::Basic || variables[i] == Var::Slack) {
			out << std::setw(columnWidth) << std::right << "x(" + std::to_string(b++) + ")";
		}
		else { out << std::setw(columnWidth) << std::right << "R(" + std::to_string(s++)+ ")"; }
	}
	out << std::setw(columnWidth) << std::right << "b" << std::endl;

	for (int i = 0; i < M.getHeight(); i++)
	{	// basis value
		if ((M.getHeight() - basis_indexes.size()) == 2) {
			if (i == 0) { out << std::setw(columnWidth) << std::left << "r"; }
			else if (i == 1) { out << std::setw(columnWidth) << std::left << "z"; }
			else { out << std::setw(columnWidth) << std::left << "col("+ std::to_string(basis_indexes[i - 2]+1) + ")"; }
		}
		else {
			if (i == 0) { out << std::setw(columnWidth) << std::left << "z"; }
			else { out << std::setw(columnWidth) << std::left << "col(" + std::to_string(basis_indexes[i - 1]+1) + ")";}
		}

		// element value
		for (int j = 0; j < M.getLength(); j++)
			out << std::setw(columnWidth) << std::right << M.data[i][j];
		out << std::endl;
	}
	out << std::endl << std::endl;
	return out;
}

// to simplyfy printing matrix
std::ostream& operator<<(std::ostream& out, const Matrix& M)
{
	for (int i = 0; i < M.getHeight(); i++)
	{
		for (int j = 0; j < M.getLength(); j++)
			out << std::setw(8) << std::left << M.data[i][j] << " ";

	}
	return out;
}
