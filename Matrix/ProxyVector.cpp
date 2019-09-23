#include "ProxyVector.h"
#include "Matrix.h"

const double& ProxyVector::operator[](int j)const
{
    // check
    return m->matrix[i * (m->n) + j];
}

double& ProxyVector::operator[](int j)
{
    // check
    return m->matrix[i * (m->n) + j];
}