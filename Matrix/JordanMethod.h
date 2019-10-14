#pragma once
#include "Matrix.h"
#include<vector>

/* Аргументы для потока */
typedef struct _ARGS
{
    const Matrix* matrix;              /* матрица */
    const std::vector<double>* b;      /* вектор */
    const std::vector<double>* x;      /* вектор */
    double* result;                     /* невязка*/
    int n;                             /* размер матрицы и векторов */
    int thread_num;                    /* номер задачи */
    int total_threads;                 /* всего задач */
} ARGS;

class MethodJordan
{
    static size_t GetNumberMaxElem(Matrix& A, size_t col_num);
    static void swap_row(Matrix& A, size_t i, size_t k);
    static void swap(double& a, double& b);
    static size_t min(size_t n1, size_t n2);
    static void PartOfResidual(ARGS args);
public:
    static std::vector<double> run(Matrix& A, std::vector<double> b);
	static double norm(const Matrix& A, const std::vector<double>& b, const std::vector<double>& x);
    static double ResidualThreads(const Matrix& A, const std::vector<double>& b, const std::vector<double>& x, int nthreads);
    static void print(const std::vector<double>& x, size_t m);
};
