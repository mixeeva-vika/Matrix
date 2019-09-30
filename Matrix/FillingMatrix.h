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
	static std::pair<Matrix, std::vector<double>> FillingWithFunc1(size_t n);
	static std::pair<Matrix, std::vector<double>> FillingWithFunc2(size_t n);
	static std::pair<Matrix, std::vector<double>> FillingWithFunc3(size_t n);
    static std::vector<double> GenerateX1(size_t n) { return std::vector<double>(n); }
    static std::vector<double> GenerateX2(size_t n) { return std::vector<double>(n); }
    static std::vector<double> GenerateX3(size_t n);
	static double CheckAnswers(std::vector<double>& x1, std::vector<double>& x2);

	///////////////////////////////////////////////////////////////
	//void TriangularView(Matrix& matrix_, std::vector<double>& b_);
	//std::vector<double> GaussMethod();
};