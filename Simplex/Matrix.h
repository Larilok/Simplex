#pragma once

#include <cmath>
#include <ctime>
#include <iomanip>
#include <vector>
#include <iostream>
#include <sstream>
#include <vcclr.h>
#include "Fraction.h"
//using namespace std;

class Matrix
{
private:
	std::vector<std::vector<Fraction>> data;

	Matrix(const Matrix& M);
	void Str2CharPtr(System::String^ str, char* chrPtr);
	//void insertColumnVector(const double *X, int &c);
	void swapRows(int& r1, int& r2);
	//Matrix cutMatrix(int& column, int& row) const;
	//void copyMatrix(const Matrix& M);
	//void makeRow_bySpinning(int &r, int &i);
	int maxElementIndexInRow(int c, int r);
public:
	Matrix() = default;
	Matrix(const int& c, const int& r);
	Matrix copy(System::Windows::Forms::DataGridView^ restrictions_table, System::Windows::Forms::DataGridView^ targetFunction);
	~Matrix();

	Fraction getElement(int row, int column);
	Fraction getEquivalent(int column);
	size_t getLength() const;
	size_t getHeight() const;

	/*Matrix& operator=(const Matrix& M);
	Matrix operator/(const double& d) const;
	Matrix operator/(Bignum second);
	Matrix operator/=(const double& d);
	Matrix operator/=(Bignum second);

	double determinant() const;
	Matrix transpone() const;
	Matrix randomize();*/

	//std::vector<int> Gauss_solution();
	std::vector<int> Jorge_Gauss_solution();
	//std::vector<int> Spinner_solution();

	int backIter(std::vector<int> &where, std::vector<Fraction> &answer);

	friend std::ostream& operator<<(std::ostream& out, const Matrix& M);
	//friend std::istream& operator>>(std::istream& in, Matrix& M);

	//void check_det_forLargeMatrix(int i, int k);
};
