#include "MATRIX.h"

#define EPS 0.00001

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

int Matrix::getLength() const
{
	return length;
}

int Matrix::getHeight() const
{
	return height;
}

//double Matrix::getEquivalent(int row)
//{
//	return ecv[row];
//}


void Matrix::Str2CharPtr(System::String^ str, char* chrPtr)
{
	// Pin memory so GC can't move it while native function is called
	pin_ptr<const wchar_t> wchPtr = PtrToStringChars(str);

	// Convert wchar_t* to char*
	size_t  convertedChars = 0;
	size_t  sizeInBytes = ((str->Length + 1) * 2);

	wcstombs_s(&convertedChars, chrPtr, sizeInBytes, wchPtr, sizeInBytes);
}

Matrix Matrix::copy(System::Windows::Forms::DataGridView ^ restrictions_table, System::Windows::Forms::DataGridView^ targetFunction)
{
	char* buffer;
	for (size_t i = 0; i < targetFunction->ColumnCount; i++)
	{
		Str2CharPtr(System::Convert::ToString(targetFunction->Rows[0]->Cells[i]->Value), buffer);
		data[0][i] = Fraction(Bignum(buffer), Bignum("1"));
	}
	for (int i = 1; i < restrictions_table->RowCount; i++) {
		for (int j = 0; j < restrictions_table->ColumnCount; j++) {
			Str2CharPtr(System::Convert::ToString(restrictions_table->Rows[i]->Cells[j]->Value), buffer);
			data[i][j] = Fraction(Bignum(buffer), Bignum("1"));
		}
	}
	return *this;
}

Matrix::Matrix() : Matrix(1, 1) {}

Matrix::Matrix(const int& c, const int& r) : data(r, std::vector<Fraction>(c, Fraction(Bignum("0"), Bignum("1")))), length(c), height(r) {}

Matrix::Matrix(const Matrix& M) : height(M.height), length(M.length)
{
	data = std::vector<std::vector<Fraction>>(height, std::vector<Fraction>(length));
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < length; j++)
			data[i][j] = M.data[i][j];
	}
}

Matrix::~Matrix()
{
	delete &data;
}



void Matrix::swapRows(int& r1, int& r2)
{
	Fraction temp;
	for (int i = 0; i < length; i++)
	{
		temp = data[r1][i];
		data[r1][i] = data[r2][i];
		data[r2][i] = temp;
	}
}


// to simplyfy printing matrix
std::ostream& operator<<(std::ostream& out, const Matrix& M)
{
	out << std::fixed << std::setprecision(3);
	for (int i = 0; i < M.height; i++)
	{
		for (int j = 0; j < M.length; j++)
			out << std::setw(8) << std::left << M.data[i][j] << " ";
		//out << std::setw(8) << std::left << M.data[i][M.length - 1] << " | " << M.ecv[i] << std::endl;

	}
	return out;
}



std::vector<int> Matrix::Jorge_Gauss_solution() {
	int i, j, r, c;

	std::vector<int> where(length, -1);            //to find arbitrary real number ( all col = 0)
	for (c = 0, r = 0; length > c && height > r; ++c) {

		int max_r_index = this->maxElementIndexInRow(c, r);
		if (Fraction::abs(data[max_r_index][c]) < 
				Fraction(Bignum(std::string(std::ostringstream(EPS).str())), Bignum("1"))) //all elements are 0 + processed float num error
			continue;

		swapRows(max_r_index, r);         // row with max el now first
		where[c] = r;               //the col isn't zero one

		for (i = 0; i < height; ++i) {
			if (i != r) {
				Fraction div_lead = data[i][c] / data[r][c];      //the a(2,1)/a(1,1)
				for (j = c; j < length; ++j)
					data[i][j] -= data[r][j] * div_lead;  //for each row below making first el = 0

				//ecv[i] -= ecv[r] * div_lead;
			}
		}
		++r;
	}
	return where;
}

int Matrix::maxElementIndexInRow(int c, int r)
{
	int max_r = r;
	for (int i = r; i < length - 1; ++i)
		if (Fraction::abs(data[i][c]) > Fraction::abs(data[max_r][c]))        //selecting max in a column
			max_r = i;
	return max_r;
}

//to fill matrix easely
//std::istream& operator>>(std::istream& in, Matrix& M)
//{
//	for (int i = 0; i < M.rows; i++) {
//		for (int j = 0; j < M.columns; j++) {
//			std::cout << "Row " << i + 1 << " column " << j + 1 << ": ";
//			in >> M.elements[i][j];
//		}
//		std::cout << " = ";
//		in >> M.ecv[i];
//		std::cout << M << std::endl;
//	}
//	return in;
//}

//Matrix& Matrix::operator=(const Matrix& M)
//{
//	copyMatrix(M);
//	return *this;
//}
//
//void Matrix::copyMatrix(const Matrix& M)
//{
//	for (int i = 0; i < rows; i++)
//		delete elements[i];
//	delete elements;
//	columns = M.columns;
//	rows = M.rows;
//	elements = new double* [rows];
//	for (int i = 0; i < rows; i++)
//		elements[i] = new double[columns];
//	for (int i = 0; i < rows; i++)
//		for (int j = 0; j < columns; j++)
//			elements[i][j] = M.elements[i][j];
//}


//void Matrix::insertColumnVector(const double* X, int& c)
//{
//	for (int i = 0; i < rows; i++)
//		elements[i][c] = X[i];
//}

//Matrix Matrix::cutMatrix(int& column, int& row) const
//{
//	Matrix cutM(columns - 1, rows - 1);
//	int iterationRow = 0;
//	for (int i = 0; i < rows; i++)
//	{
//		if (i == row)
//			continue;
//		int ic = 0;
//		for (int j = 0; j < columns; j++)
//		{
//			if (j == column)
//				continue;
//			cutM.elements[iterationRow][ic] = elements[i][j];
//			ic++;
//		}
//		iterationRow++;
//	}
//	return cutM;
//}

//
//Matrix Matrix::operator/(const double& d) const
//{
//	if (d == 0.0)
//		throw std::exception("You cannot divide by 0");
//	Matrix prodM(columns, rows);
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < columns; j++)
//			prodM.elements[i][j] = elements[i][j] / d;
//		prodM.ecv[i] = ecv[i] / d;
//	}
//	return prodM;
//}
//
//Matrix Matrix::operator/=(const double& d)
//{
//	*this = *this / d;
//	return *this;
//}

//double Matrix::determinant() const
//{
//	if (columns != rows)
//		throw std::exception("Error - given matrix is not a square matrix");
//	double determinant = 0.0;
//	if (columns == 1)
//		return determinant = elements[0][0];
//	else
//	{
//		for (int i = 0; i < columns; i++)
//		{
//			int r = 0;
//			Matrix cutM = cutMatrix(i, r);
//			determinant += elements[r][i] * pow(-1, i) * cutM.determinant();
//		}
//		return determinant;
//	}
//}

//void Matrix::check_det_forLargeMatrix(int i, int k) {
//	int max_i = -1;
//
//	for (i = k; i < rows; i++) {
//		if (fabs(elements[i][k]) > 0) {
//			max_i = i;
//		}
//	}
//
//
//	if (max_i == -1) {
//		throw std::exception("Error: det=0");
//
//	}
//}

//Matrix Matrix::randomize()
//{
//	srand((unsigned int)time(NULL));
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < columns; j++)
//			elements[i][j] = rand() % 101;
//		ecv[i] = rand() % 101;
//	}
//	return *this;
//}


//Matrix Matrix::transpone() const
//{
//	Matrix transponedM(rows, columns);
//	for (int i = 0; i < rows; i++)
//		for (int j = 0; j < columns; j++)
//			transponedM.elements[j][i] = elements[i][j];
//	return transponedM;
//}


//std::vector<int> Matrix::Gauss_solution() {
//	int i = 0, j = 0, r = 0, c = 0;
//	std::vector<int> where(columns, -1);            //to find arbitrary real number ( all col = 0)
//	for (; c < columns && r < rows; c++) {
//
//			int max_r_index = this->maxElementIndexInRow(c, r);
//		if (abs(elements[max_r_index][c]) < EPS)         //all elements are 0 + processed float num error
//			continue;
//
//		swapRows(max_r_index, r);         // row with max el now first
//		where[c] = r;               //the col isn't zero one
//
//		for (i = r + 1; i < rows; i++) {
//
//			double divider = elements[i][c] / elements[r][c];
//			elements[i][c] = 0;           //element lower = 0
//			for (j = c + 1; j < columns; ++j) {
//				elements[i][j] -= elements[r][j] * divider;
//			}
//			ecv[i] -= ecv[r] * divider;
//		}
//		r++;
//	}
//	return where;
//}


//void Matrix::makeRow_bySpinning(int &r, int &i) {
//	double sin,cos,hipotenusa, temp;
//	hipotenusa = sqrt((elements[r][r] * elements[r][r] + elements[i][r] * elements[i][r]));
//	sin = elements[r][r] / hipotenusa;
//	cos = elements[i][r] / hipotenusa;
//
//	for (int j = r; j < columns; ++j) {
//		temp = elements[r][j];
//		elements[r][j] = elements[r][j] * sin + elements[i][j] * cos;	//top element
//		elements[i][j] = temp * cos - elements[i][j] * sin;				//lower element
//	}
//	temp = ecv[r];
//	ecv[r] = ecv[r] * sin + ecv[i] * cos;
//	ecv[i] = temp * cos - ecv[i] * sin;
//
//}


//int Matrix::backIter(std::vector<int> &where ,std::vector<double> &answer) {
//
//	int r = rows - 1, k = columns - 1, i, j;
//	answer.assign(columns, 0);
//
//	while (k >= 0 && r >= 0) {
//		if (where[r] != -1 ) {
//			answer[k] = ecv[r] / elements[where[r]][k];	//diagonal elem(k) / b(k)
//
//			for (i = k + 1; i < columns; i++)
//				answer[k] -= elements[k][i] * answer[i] / elements[k][k];  //insert x and solve
//		}
//		else if(ecv[k])throw std::exception("Error!\ndet = 0");
//		k--, r--;
//	}
//	for (i = 0; i < rows; ++i) {       //checking is answer take a place at all
//		double sum = 0;
//		for (j = 0; j < columns; ++j) 
//			sum += answer[j] * elements[i][j];     //solving left part
//
//		if (abs(sum - ecv[i]) > EPS)            //something went complitely wrong
//			return 0;
//
//	}
//
//	for (i = 0; i < columns; ++i)
//		if (where[i] == -1)
//			return 2;
//
//	return 1;
//
//}
//std::vector<int> Matrix::Spinner_solution() {
//	int i, r, c;
//
//	std::vector<int> where(columns, -1);            //to check whether the column is absolute 0
//	for (c = 0, r = 0; columns > c && rows > r; ++c) {
//		int max_r = this->maxElementIndexInRow(c, r);
//		if (abs(elements[max_r][c]) < EPS)         //all elements are 0 + processed float num error
//			continue;
//		swapRows(max_r, r);         // row with max el now first
//		where[c] = r;               //the row isn't zero one
//
//
//		for (i = r + 1; i < rows; ++i) {
//			makeRow_bySpinning(r, i);
//		}
//		++r;
//	}
//	return where;
//}
//
