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
