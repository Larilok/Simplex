#pragma once
enum Var
{
	Basic,
	Slack,
	Surplus
};

void simplex_solution(const Matrix m, bool min_max);
