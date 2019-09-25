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
	static std::pair<Matrix, std::vector<double>> FillingWithFunc(size_t n);
};