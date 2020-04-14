#pragma once

#include <cmath>
#include <ctime>
#include <iomanip>
#include <vector>
#include <iostream>
//using namespace std;
class Matrix
{
private:
	double** elements;
	int columns;
	int rows;
	double* ecv;

	Matrix(const Matrix& M);
	void insertColumnVector(const double *X, int &c);
	void swapRows(int& r1, int& r2);
	Matrix cutMatrix(int& column, int& row) const;
	void copyMatrix(const Matrix& M);
	void makeRow_bySpinning(int &r, int &i);
	int maxElementIndexInRow(int c, int r);
public:
	double getElement(int row, int column);
	double getEquivalent(int column);
	Matrix copy(System::Windows::Forms::DataGridView^  matrix_table);
	Matrix();
	Matrix(const int& c, const int& r);
	~Matrix();
	Matrix& operator=(const Matrix& M);
	Matrix operator/(const double& d) const;
	Matrix operator/=(const double& d);
	double determinant() const;
	int getColumns() const;
	int getRows() const;
	Matrix transpone() const;
	Matrix randomize();

	std::vector<int> Gauss_solution();
	std::vector<int> Jorge_Gauss_solution();
	std::vector<int> Spinner_solution();

	int backIter(std::vector<int> &where, std::vector<double> &answer);

	friend std::ostream& operator<<(std::ostream& out, const Matrix& M);
	friend std::istream& operator>>(std::istream& in, Matrix& M);

	void check_det_forLargeMatrix(int i, int k);
};
