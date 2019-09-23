#include "JordanMethod.h"
#include "FillingMatrix.h"

void help()
{
    std::cout << "Enter the size of the matrix of type int" << std::endl;
    std::cout << "Then enter the matrix of this size" << std::endl;
}

int main(int argc, char* argv[])
{
    try
    {
        std::pair<Matrix, std::vector<double>> res;
        if (argc > 2)
            throw "Incorrect number of argument";
        if (argc == 2)
        {
            res = FillingData::FillingFromFile(argv[1]);
        }
        if (argc == 1)
        {
            help();
            for (;;)
            {
                try
                {
                    res = FillingData::FillingFromKeyboar();
                    break;
                }
                catch (char* exp)
                {
                    help();
                }
            }
        }
        //std::pair<Matrix, std::vector<double>> res;
        //res = FillingData::FillingFromFile("a.txt");
        std::cout << res.first << std::endl;

        for (int i = 0; i < res.second.size(); ++i)
            std::cout << res.second[i] << " ";
        std::cout << std::endl;

        std::vector<double> x = MethodJordan::run(res.first, res.second);
        for (int i = 0; i < x.size(); ++i)
            std::cout << x[i] << " ";
        std::cout << std::endl;
    }
    catch (char* exp)
    {
        std::cout << exp << std::endl;
    }
    /*
    double ar[] = {
    1, 2, 3,
    4, 15, 6,
    7, 8, 9 };

    Matrix a(ar, 3);
    std::vector<double> b = { 1, 2, 3 };
    //a[1][2] = 15;
    //double b1 = a[1][2];
    //a[1][2] = a[1][3];
    //const Matrix b(a);
    //b1 = b[0][1];
    //std::pair<size_t, double> pair_ = MethodJordan::GetNumberMaxElem(a, 1);
    //std::cout << pair_.first << " " << pair_.second << std::endl;
    //MethodJordan::swap_row(a, 1, 2);
    //std::cout << a << std::endl;
    MethodJordan::run(a, b);
    */

    system("pause");
    return 0;
}