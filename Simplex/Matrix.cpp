#include "MATRIX.h"

#define EPS 0.00001

double Matrix::getElement(int row, int column)
{
	return elements[row][column];
}

double Matrix::getEquivalent(int row)
{
	return ecv[row];
}

Matrix Matrix::copy(System::Windows::Forms::DataGridView ^ matrix_table)
{
	for (int i = 0; i < matrix_table->RowCount; i++) {
		for (int j = 0; j < matrix_table->ColumnCount - 1; j++)
			elements[i][j] = System::Convert::ToDouble(matrix_table->Rows[i]->Cells[j]->Value);
		ecv[i] = System::Convert::ToDouble(matrix_table->Rows[i]->Cells[matrix_table->Columns->Count - 1]->Value);
	}
	return *this;
}

Matrix::Matrix() : Matrix(1, 1) {}

Matrix::Matrix(const int& c, const int& r) : columns(c), rows(r)
{
	elements = new double*[rows];
	ecv = new double[rows];
	for (int i = 0; i < rows; i++)
		elements[i] = new double[columns];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			elements[i][j] = 0;
		ecv[i] = 0;
	}
}

Matrix::Matrix(const Matrix& M) : columns(M.columns), rows(M.rows)
{
	elements = new double*[rows];
	ecv = new double[rows];
	for (int i = 0; i < rows; i++)
		elements[i] = new double[columns];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			elements[i][j] = M.elements[i][j];
		ecv[i] = M.ecv[i];
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
		delete elements[i];
	delete elements;
	delete ecv;
}

Matrix& Matrix::operator=(const Matrix& M)
{
	copyMatrix(M);
	return *this;
}


void Matrix::insertColumnVector(const double* X, int& c)
{
	for (int i = 0; i < rows; i++)
		elements[i][c] = X[i];
}

Matrix Matrix::cutMatrix(int& column, int& row) const
{
	Matrix cutM(columns - 1, rows - 1);
	int iterationRow = 0;
	for (int i = 0; i < rows; i++)
	{
		if (i == row)
			continue;
		int ic = 0;
		for (int j = 0; j < columns; j++)
		{
			if (j == column)
				continue;
			cutM.elements[iterationRow][ic] = elements[i][j];
			ic++;
		}
		iterationRow++;
	}
	return cutM;
}

void Matrix::swapRows(int& r1, int& r2)
{
	double temp = 0;
	for (int i = 0; i < columns; i++)
	{
		temp = elements[r1][i];
		elements[r1][i] = elements[r2][i];
		elements[r2][i] = temp;
	}
	temp = ecv[r1];
	ecv[r1] = ecv[r2];
	ecv[r2] = temp;
}


Matrix Matrix::operator/(const double& d) const
{
	if (d == 0.0)
		throw std::exception("You cannot divide by 0");
	Matrix prodM(columns, rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			prodM.elements[i][j] = elements[i][j] / d;
		prodM.ecv[i] = ecv[i] / d;
	}
	return prodM;
}

Matrix Matrix::operator/=(const double& d)
{
	*this = *this / d;
	return *this;
}

double Matrix::determinant() const
{
	if (columns != rows)
		throw std::exception("Error - given matrix is not a square matrix");
	double determinant = 0.0;
	if (columns == 1)
		return determinant = elements[0][0];
	else
	{
		for (int i = 0; i < columns; i++)
		{
			int r = 0;
			Matrix cutM = cutMatrix(i, r);
			determinant += elements[r][i] * pow(-1, i) * cutM.determinant();
		}
		return determinant;
	}
}

void Matrix::check_det_forLargeMatrix(int i, int k) {
	int max_i = -1;

	for (i = k; i < rows; i++) {
		if (fabs(elements[i][k]) > 0) {
			max_i = i;
		}
	}


	if (max_i == -1) {
		throw std::exception("Error: det=0");

	}
}

Matrix Matrix::randomize()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			elements[i][j] = rand() % 101;
		ecv[i] = rand() % 101;
	}
	return *this;
}

void Matrix::copyMatrix(const Matrix& M)
{
	for (int i = 0; i < rows; i++)
		delete elements[i];
	delete elements;
	columns = M.columns;
	rows = M.rows;
	elements = new double*[rows];
	for (int i = 0; i < rows; i++)
		elements[i] = new double[columns];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			elements[i][j] = M.elements[i][j];
}

Matrix Matrix::transpone() const
{
	Matrix transponedM(rows, columns);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			transponedM.elements[j][i] = elements[i][j];
	return transponedM;
}

int Matrix::getColumns() const
{
	return columns;
}

int Matrix::getRows() const
{
	return rows;
}

// to simplyfy printing matrix
std::ostream& operator<<(std::ostream& out, const Matrix& M)
{
	out << std::fixed << std::setprecision(3);
	for (int i = 0; i < M.rows; i++)
	{
		for (int j = 0; j < M.columns - 1; j++)
			out << std::setw(8) << std::left << M.elements[i][j] << " ";
		out << std::setw(8) << std::left << M.elements[i][M.columns - 1] << " | " << M.ecv[i] << std::endl;

	}
	return out;
}

//to fill matrix easely
std::istream& operator>>(std::istream& in, Matrix& M)
{
	for (int i = 0; i < M.rows; i++) {
		for (int j = 0; j < M.columns; j++) {
			std::cout << "Row " << i + 1 << " column " << j + 1 << ": ";
			in >> M.elements[i][j];
		}
		std::cout << " = ";
		in >> M.ecv[i];
		std::cout << M << std::endl;
	}
	return in;
}

std::vector<int> Matrix::Jorge_Gauss_solution() {
	int i, j, r, c;

	std::vector<int> where(columns, -1);            //to find arbitrary real number ( all col = 0)
	for (c = 0, r = 0; columns > c && rows > r; ++c) {

		int max_r_index = this->maxElementIndexInRow(c, r);
		if (abs(elements[max_r_index][c]) < EPS)         //all elements are 0 + processed float num error
			continue;

		swapRows(max_r_index, r);         // row with max el now first
		where[c] = r;               //the col isn't zero one

		for (i = 0; i < rows; ++i) {
			if (i != r) {
				double div_lead = elements[i][c] / elements[r][c];      //the a(2,1)/a(1,1)
				for (j = c; j < columns; ++j)
					elements[i][j] -= elements[r][j] * div_lead;  //for each row below making first el = 0

				ecv[i] -= ecv[r] * div_lead;
			}
		}
		++r;
	}
	return where;
}

std::vector<int> Matrix::Gauss_solution() {
	int i = 0, j = 0, r = 0, c = 0;
	std::vector<int> where(columns, -1);            //to find arbitrary real number ( all col = 0)
	for (; c < columns && r < rows; c++) {

			int max_r_index = this->maxElementIndexInRow(c, r);
		if (abs(elements[max_r_index][c]) < EPS)         //all elements are 0 + processed float num error
			continue;

		swapRows(max_r_index, r);         // row with max el now first
		where[c] = r;               //the col isn't zero one

		for (i = r + 1; i < rows; i++) {

			double divider = elements[i][c] / elements[r][c];
			elements[i][c] = 0;           //element lower = 0
			for (j = c + 1; j < columns; ++j) {
				elements[i][j] -= elements[r][j] * divider;
			}
			ecv[i] -= ecv[r] * divider;
		}
		r++;
	}
	return where;
}


void Matrix::makeRow_bySpinning(int &r, int &i) {
	double sin,cos,hipotenusa, temp;
	hipotenusa = sqrt((elements[r][r] * elements[r][r] + elements[i][r] * elements[i][r]));
	sin = elements[r][r] / hipotenusa;
	cos = elements[i][r] / hipotenusa;

	for (int j = r; j < columns; ++j) {
		temp = elements[r][j];
		elements[r][j] = elements[r][j] * sin + elements[i][j] * cos;	//top element
		elements[i][j] = temp * cos - elements[i][j] * sin;				//lower element
	}
	temp = ecv[r];
	ecv[r] = ecv[r] * sin + ecv[i] * cos;
	ecv[i] = temp * cos - ecv[i] * sin;

}

int Matrix::maxElementIndexInRow(int c, int r)
{
	int max_r = r;
	for (int i = r; i < rows; ++i)
		if (abs(elements[i][c]) > abs(elements[max_r][c]))        //selecting max in a column
			max_r = i;
	return max_r;
}

int Matrix::backIter(std::vector<int> &where ,std::vector<double> &answer) {

	int r = rows - 1, k = columns - 1, i, j;
	answer.assign(columns, 0);

	while (k >= 0 && r >= 0) {
		if (where[r] != -1 ) {
			answer[k] = ecv[r] / elements[where[r]][k];	//diagonal elem(k) / b(k)

			for (i = k + 1; i < columns; i++)
				answer[k] -= elements[k][i] * answer[i] / elements[k][k];  //insert x and solve
		}
		else if(ecv[k])throw std::exception("Error!\ndet = 0");
		k--, r--;
	}
	for (i = 0; i < rows; ++i) {       //checking is answer take a place at all
		double sum = 0;
		for (j = 0; j < columns; ++j) 
			sum += answer[j] * elements[i][j];     //solving left part

		if (abs(sum - ecv[i]) > EPS)            //something went complitely wrong
			return 0;

	}

	for (i = 0; i < columns; ++i)
		if (where[i] == -1)
			return 2;

	return 1;

}
std::vector<int> Matrix::Spinner_solution() {
	int i, r, c;

	std::vector<int> where(columns, -1);            //to check whether the column is absolute 0
	for (c = 0, r = 0; columns > c && rows > r; ++c) {
		int max_r = this->maxElementIndexInRow(c, r);
		if (abs(elements[max_r][c]) < EPS)         //all elements are 0 + processed float num error
			continue;
		swapRows(max_r, r);         // row with max el now first
		where[c] = r;               //the row isn't zero one


		for (i = r + 1; i < rows; ++i) {
			makeRow_bySpinning(r, i);
		}
		++r;
	}
	return where;
}

