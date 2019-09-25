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

std::pair<Matrix, std::vector<double>> FillingData::FillingWithFunc(size_t n)
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



















