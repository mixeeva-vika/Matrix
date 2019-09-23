#include "JordanMethod.h"
#include "FillingMatrix.h"

std::size_t MethodJordan::GetNumberMaxElem(Matrix& A, size_t col_num)
{
    double max = 0;
    size_t number = 0;
    size_t n = A.size();
    for (size_t i = col_num; i < n; ++i)
    {
        if (abs(A[i][col_num]) > max)
        {
            max = abs(A[i][col_num]);
            number = i;
        }
    }
    return number;
}

void MethodJordan::swap(double& a, double& b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

void MethodJordan::swap_row(Matrix& A, size_t i, size_t k)
{
    size_t n = A.size();
    for (size_t j = 0; j < n; ++j)
    {
        swap(A[i][j], A[k][j]);
    }
}

std::vector<double> MethodJordan::run(Matrix& A, std::vector<double> b)
{
    Matrix M = A;
    for (size_t i = 0; i < M.size(); ++i)
    {
       // std::cout << "=================" << i << "==============" << std::endl;
        size_t max_num = GetNumberMaxElem(M, i);
        if (max_num != i)
        {
            swap_row(M, i, max_num);
            swap(b[i], b[max_num]);
        }
        double max_elem = M[i][i];
        //std::cout << "After swap" << std::endl << M << std::endl;
        //for(int idx = 0; idx < b.size(); ++idx)
         //   std::cout << b[idx]<< " ";
        //std::cout << std::endl;

        for (size_t j = i; j < M.size(); ++j)
        {
            double new_elem = M[i][j] / max_elem;
            M[i][j] = new_elem;
        }
        b[i] = b[i] / max_elem;

        //std::cout << "After current change" << std::endl << M << std::endl;
        //for (int idx = 0; idx < b.size(); ++idx)
        //    std::cout << b[idx] << " ";
        //std::cout << std::endl;


        for (size_t k = 0; k < M.size(); ++k)
        {
            if (k == i)
                continue;
            double coef = M[k][i];
            for (size_t j = i; j < M.size(); ++j)
            {
                double new_elem = M[k][j] - coef * M[i][j];
                M[k][j] = new_elem;

                //std::cout << "new_elem = " << new_elem << std::endl << M << std::endl;
            }
			b[k] = b[k] - coef * b[i];
        }

        //std::cout << "After all" << std::endl << M << std::endl;
        //for (int idx = 0; idx < b.size(); ++idx)
        //    std::cout << b[idx] << std::endl;
        //int ah = 5;
    }
    //std::cout << M << std::endl;
	std::vector<double> x(M.size());
	for (size_t i = 0; i < x.size(); ++i)
	{
		x[i] = b[i];
	}

	return x;
}








