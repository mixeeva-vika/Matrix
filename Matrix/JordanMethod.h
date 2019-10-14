#pragma once
#include "Matrix.h"
#include<vector>

/* ��������� ��� ������ */
typedef struct _ARGS
{
    const Matrix* matrix;              /* ������� */
    const std::vector<double>* b;      /* ������ */
    const std::vector<double>* x;      /* ������ */
    double* result;                     /* �������*/
    int n;                             /* ������ ������� � �������� */
    int thread_num;                    /* ����� ������ */
    int total_threads;                 /* ����� ����� */
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
