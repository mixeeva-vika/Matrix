#pragma once
#include "Matrix.h"
#include<vector>

class MethodJordan
{
    static size_t GetNumberMaxElem(Matrix& A, size_t col_num);
    static void swap_row(Matrix& A, size_t i, size_t k);
    static void swap(double& a, double& b);
    static size_t min(size_t n1, size_t n2);
public:
    static std::vector<double> run(Matrix& A, std::vector<double> b);
	static size_t norm(const Matrix& A, const std::vector<double>& b, const std::vector<double>& x);
    static void print(const std::vector<double>& x, size_t m);
};
