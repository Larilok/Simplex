#pragma once

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <iostream>
#include <sstream>
#include <vcclr.h>
#include "Fraction.h"

enum Var
{
	Basic,
	Slack,
	Surplus
};

class Matrix
{
private:
	std::vector<std::vector<Fraction>> data;

	void Str2CharPtr(System::String^ str, std::string& sstring);
	void insert_nonbasic_variable_simplex(std::vector<size_t>& variables,
		std::vector<size_t>& basis, 
		Var type, std::string value,
		size_t &current_row);
	void swapRows(int& r1, int& r2);
	//Matrix cutMatrix(int& column, int& row) const;
	//void copyMatrix(const Matrix& M);
	//void makeRow_bySpinning(int &r, int &i);
	int maxElementIndexInRow(int c, int r);
public:
	Matrix();
	Matrix(const int& c, const int& r);
	Matrix(const Matrix& M);
	Matrix(System::Windows::Forms::DataGridView^ restrictions_table,
		System::Windows::Forms::DataGridView^ targetFunction, 
		std::vector<size_t>& variables,
		std::vector<size_t>& basis);
	~Matrix();

	Fraction getElement(int row, int column);
	Fraction getEquivalent(int column);
	std::size_t getLength() const;
	std::size_t getHeight() const;

	/*Matrix& operator=(const Matrix& M);
	Matrix operator/(const double& d) const;
	Matrix operator/(Bignum second);
	Matrix operator/=(const double& d);
	Matrix operator/=(Bignum second);

	double determinant() const;
	Matrix transpone() const;
	Matrix randomize();*/

	//std::vector<int> Gauss_solution();
	void simplex_solution(const bool& min_max, std::vector<size_t>& variables, std::vector<size_t>& basis_indexes);
	std::vector<int> Jorge_Gauss_solution();
	//std::vector<int> Spinner_solution();

	int backIter(std::vector<int> &where, std::vector<Fraction> &answer);

	friend std::ostream& operator<<(std::ostream& out, const Matrix& M);
	//friend std::istream& operator>>(std::istream& in, Matrix& M);

	//void check_det_forLargeMatrix(int i, int k);
};
