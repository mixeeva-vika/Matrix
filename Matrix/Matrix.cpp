#include "Matrix.h"

Matrix::Matrix(const double* matrix_, size_t n_)
{
    n = n_;
    matrix = new double[n * n];
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            matrix[i * n + j] = matrix_[i * n + j];
        }
    }
}

Matrix::Matrix(size_t n_)
{
    n = n_;
    matrix = new double[n * n];
}

Matrix::Matrix(const Matrix& S)
{
    n = S.n;
    matrix = new double[n * n];
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            matrix[i * n + j] = S.matrix[i * n + j];
        }
    }
}

Matrix::~Matrix()
{
    delete[] matrix;
}

Matrix& Matrix::operator=(const Matrix& M)
{
    if (n != M.n)
    {
        n = M.n;
        delete[] matrix;
        matrix = new double[n * n];
    }
    memcpy(matrix, M.matrix, n*n*sizeof(double));
    return *this;
}

std::vector<double> Matrix::operator*(const std::vector<double>& x) const
{
    size_t n = size();
    double sum;
    std::vector<double> b(n);
    for (size_t i = 0; i < n; ++i)
    {
        sum = 0;
        for (size_t j = 0; j < n; ++j)
        {
            sum += (*this)[i][j] * x[j];
        }
        b[i] = sum;
    }

    return b;
}

std::vector<double> Matrix::MultiplyPartOfMatrix(const std::vector<double>& x, int thread_num, int nthreads) const
{
    /* Первая участвующая строка матрицы */
    int first_row = n * thread_num;
    first_row /= nthreads;
    /* Последняя участвующая строка матрицы */
    int last_row = n * (thread_num + 1);
    last_row = last_row / nthreads - 1;

    std::vector<double> res(last_row - first_row + 1);
    double* p = matrix + first_row * n;
    int k = 0;
    for (int i = first_row; i <= last_row; i++)
    {
        double s = 0;
        for (int j = 0; j < n; j++)
            s += *(p++) * x[j];
        res[k] = s;
        ++k;
    }
    return res;
}

ProxyVector Matrix::operator[](int i) const
{
    return ProxyVector(this, i);
}

std::ostream& operator<<(std::ostream& out, const Matrix& S)
{
    out << S.n << std::endl;
    for (size_t i = 0; i < S.n; ++i)
    {
        for (size_t j = 0; j < S.n; ++j)
        {
            out << S.matrix[i * S.n + j] << " ";
        }
        out << std::endl;
    }
    out << std::endl;
    return out;
}
