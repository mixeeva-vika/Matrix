#include "JordanMethod.h"
#include "FillingMatrix.h"

void help()
{
    std::cout << "Enter the size of the matrix of type int" << std::endl;
    std::cout << "Then enter the matrix of this size" << std::endl;

    std::cout << "It is look like : " << std::endl;
    std::cout << "n " << std::endl;
    std::cout << "a_{1,1} . . . a_{1,n} b_{1}" << std::endl;
    std::cout << "a_{2,1} . . . a_{2,n} b_{2}" << std::endl;
    std::cout << ". . .  . . .  . . .  . . . " << std::endl;
    std::cout << "a_{n,1} . . . a_{n,n} b_{n}" << std::endl;
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
		std::cout << "Solution : " << std::endl;
        for (int i = 0; i < x.size(); ++i)
            std::cout << x[i] << " ";
        std::cout << std::endl;
    }
    catch (char* exp)
    {
        std::cout << exp << std::endl;
    }
    
    system("pause");
    return 0;
}