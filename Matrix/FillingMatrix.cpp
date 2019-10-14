#include "FillingMatrix.h"

double FillingData::read(std::istream& fin)
{
    double x;
    if (fin >> x)
    {
        return x;
    }
    else if (fin.bad())
        throw "Reading error";
    else if (fin.eof())
        throw "Incorrect size of matrix or incorrect file";
    else
        throw "Incorrect format";
}

std::pair<Matrix, std::vector<double>> FillingData::ReadSystem(std::istream& fin)
{
    size_t n;
    fin >> n;
    Matrix A(n);
    std::vector<double> b(n);
    int tmp;
	for(size_t i = 0; i < n; ++i)
	{
		for(size_t j = 0; j < n; ++j)
		{
            A[i][j] = read(fin);
		}
        b[i] = read(fin);
	}
    fin >> tmp;
    if (!fin.eof())
        throw "Incorrect file";

    return std::pair<Matrix, std::vector<double>>(A, b);
}

std::pair<Matrix, std::vector<double>> FillingData::FillingFromKeyboar()
{
    return ReadSystem(std::cin);
}

std::pair<Matrix, std::vector<double>> FillingData::FillingFromFile(char* filename)
{
    std::ifstream fin(filename);
    if (!fin)
        throw "Can't open the file";

    try
    {
        std::pair<Matrix, std::vector<double>> result = ReadSystem(fin);
        fin.close();
        return result;
    }
    catch (char* err)
    {
        fin.close();
        throw;
    }
}

std::pair<Matrix, std::vector<double>> FillingData::FillingWithFunc1(size_t n)
{
	Matrix A(n);
	std::vector<double> b(n);
	b[0] = 1;
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			A[i][j] = 1. / (i + j + 1);
		}
	}
	for (size_t i = 1; i < n; ++i)
		b[i] = 0;
    
    return std::make_pair(A, b);
}

std::pair<Matrix, std::vector<double>> FillingData::FillingWithFunc2(size_t n)
{
	Matrix A(n);
	std::vector<double> b(n);
	for (size_t i = 0; i < n; ++i)
	{
        using namespace std;
        //cout << "i = " << i << endl;
		for (size_t j = 0; j < n; ++j)
		{
			if (j == i)
			{
				if (i == 0)
					A[i][j] = -1;
				else if (i == n - 1)
					A[i][j] = -((double)(n - 1) / n);
                else
				    A[i][j] = -2;
			}
            else
            {
                if ((j == i + 1) || (j == i - 1))
                    A[i][j] = 1;
                else
                    A[i][j] = 0;
            }
            //cout << "j = " << i << endl;
            //cout << A << endl;
		}
        
      
	}
	for (size_t i = 0; i < n - 1; ++i)
		b[i] = 0;
	b[n - 1] = 1;
	return std::make_pair(A, b);
}
//===================================----2----============================================
std::pair<Matrix, std::vector<double>> FillingData::FillingWithFunc3(size_t n)
{
	Matrix A(n);
	std::vector<double> b(n);
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			A[i][j] = 1. / (i + j + 1);
			if (j  % 2 == 1)
				b[i] += A[i][j];
		}
	}
	return std::make_pair(A, b);
}

std::vector<double> FillingData::GenerateX3(size_t n)
{
    std::vector<double> x(n);
    for (size_t i = 0; i < x.size(); ++i)
    {
        if (i % 2 != 0)
            x[i] = 1;
        else 
            x[i] = 0;
    }
    return x;
}
double FillingData::CheckAnswers(std::vector<double>& x1, std::vector<double>& x2)
{
	double sum = 0;
	for (size_t i = 0; i < x1.size(); ++i)
		sum += (x1[i] - x2[i]) * (x1[i] - x2[i]);
	return sqrt(sum);
}


///////////////////////////////////////////////////////////////////////////////////
//void FillingData::TriangularView(Matrix& matrix_, std::vector<double>& b_)
//{
//	int k = 0;
//	while (k < matrix_.n)
//	{
//		if (matrix_[k][k] == 0)
//		{
//			for (int i = k + 1; i < matrix_.size(); ++i)
//			{
//				if (matrix_[i][k] != 0)
//				{
//					MethodJordan::swap_row(matrix_, i, k);
//					MethodJordan::swap(b_[k], b_[i]);
//				}
//			}
//		}
//		if (matrix_[k][k] != 0)
//		{
//			double tmp = matrix_[k][k];
//			for (int i = k; i < matrix_[k].n; ++i)
//			{
//				matrix_[k][i] = matrix_[k][i] / tmp;
//
//			}
//
//			b_[k] = (b_[k] / tmp);
//
//			for (int i = k + 1; i < matrix_.size(); ++i)
//			{
//				double tmp = matrix_[i][k];
//				for (int j = k; j < matrix_[k].n; ++j)
//				{
//					matrix_[i][j] -= tmp * matrix_[k][j];
//				}
//				b_[i] -= tmp * b_[k];
//			}
//		}
//		++k;
//	}
//
//}
//
//std::vector<double> FillingData::GaussMethod()
//{
//	Matrix matrix_ = ??;
//	std::vector<double> b_ = ??;
//	TriangularView(matrix_, b_);
//	std::vector<double> x(matrix.n);
//	for (int k = x.size() - 1; k >= 0; --k)
//	{
//		x[k] = b_[k];
//		for (int i = 0; i < k; ++i)
//			b_[i] = b_[i] - matrix_[i][k] * x[k];
//	}
//	return x;
//}
