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
	void deleteSurplusColumn(std::size_t c);
	int minRatioIndexInColumn(int c);
	int maxMinIndexInRow(int r, const bool min_max);
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

	void simplex_solution(std::ostream& logs, const bool& min_max, std::vector<size_t>& variables, std::vector<size_t>& basis_indexes);
	int backIter(std::vector<size_t> &where, std::vector<Fraction> &answer);

	std::ostream& printSimplexMatrix(std::ostream& out, const Matrix& M, const std::vector<size_t>& variables, const std::vector<size_t>& basis_indexes);
	friend std::ostream& operator<<(std::ostream& out, const Matrix& M);

};
