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
int toInt(const char*s, int*xp)
{
    long l;
    char* e;
    errno = 0;
    l = strtol(s, &e, 10);
    if (!errno && *e == '\0')
    {
        if (INT_MIN <= l && l <= INT_MAX)
        {
            *xp = (int)l;
            return 0; // Good
        }
    }
    return -1; // Bad
}
int main(int argc, char* argv[])
{
    int flag = 0;
    try
    {
        std::pair<Matrix, std::vector<double>> res;
        if (argc > 2)
            throw "Incorrect number of argument";
        if (argc == 2)
        {
            int xp;
            if (toInt(argv[1], &xp) == -1)
                res = FillingData::FillingFromFile(argv[1]);
            else
            {
                if (xp < 1)
                    throw "Incorrect data";
                flag = 1;
                res = FillingData::FillingWithFunc(xp);
            }
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
        
        std::cout << res.first << std::endl;

        for (int i = 0; i < res.second.size(); ++i)
            std::cout << res.second[i] << " ";
        std::cout << std::endl;

        std::vector<double> x = MethodJordan::run(res.first, res.second);
        std::cout << "Solution : " << std::endl;
        size_t m = 30;
        MethodJordan::print(x, m);
        std::cout << "Residual : " << std::endl;
        std::cout << MethodJordan::norm(res.first, res.second, x) << std::endl;
        if (flag == 1)
        {
            for (size_t i = 0; i < x.size(); ++i)
                std::cout << x[i] << std::endl;
        }
    }
    catch (char* exp)
    {
        std::cout << exp << std::endl;
    }
    
    system("pause");
    return 0;
}