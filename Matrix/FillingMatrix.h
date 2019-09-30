#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Matrix.h"

class FillingData
{
    static double read(std::istream& fin);
    static std::pair<Matrix, std::vector<double>> ReadSystem(std::istream& fin);
public:
    static std::pair<Matrix, std::vector<double>> FillingFromKeyboar();
    static std::pair<Matrix, std::vector<double>> FillingFromFile(char* filename);
	static std::pair<Matrix, std::vector<double>> FillingWithFunc_1(size_t n);
	static std::pair<Matrix, std::vector<double>> FillingWithFunc_2(size_t n);
	static std::pair<Matrix, std::vector<double>> FillingWithFunc_1_1(size_t n);
	static int CheckForFunc_1_1(std::vector<double>& x);

	///////////////////////////////////////////////////////////////
	void TriangularView(Matrix& matrix_, std::vector<double>& b_);
	std::vector<double> GaussMethod();
};