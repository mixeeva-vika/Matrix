#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<fstream>
#include "ProxyVector.h"

class Matrix
{
    double* matrix;
    size_t n;
public:
    Matrix() : matrix(nullptr), n(0) {}
    Matrix(const double* matrix_, size_t n_);
    Matrix(size_t n_);
    Matrix(const Matrix& S);
    ~Matrix();

    Matrix& operator=(const Matrix& M);
    ProxyVector operator[](int i) const;
    size_t size() const { return n; }

    std::vector<double> operator*(const std::vector<double>& x) const;//////!!!

    friend std::ostream& operator<<(std::ostream& out, const Matrix& S);
    friend ProxyVector;
};
