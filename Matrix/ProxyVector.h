#pragma once
class Matrix;

class ProxyVector
{
    const Matrix* m;
    int i;
public:
    ProxyVector(const Matrix* _m, int _i) : m(_m), i(_i) {}
    const double& operator[](int j) const;
    double& operator[](int j);
};

