#include "JordanMethod.h"
#include "FillingMatrix.h"
#include <time.h>
#include <chrono>

/* Суммарное время работы всех задач */
static long int threads_total_time = 0;

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
    /* число создаваемых задач */
    int nthreads;
    /* астрономическое время работы всего процесса */
    long int t_full;

    int flag = 0;
    try
    {
        std::pair<Matrix, std::vector<double>> res;
        if (argc > 4)
            throw "Incorrect number of argument";
        if (argc == 3)
        {
            res = FillingData::FillingFromFile(argv[1]);
            if (toInt(argv[2], &nthreads) == -1)
                throw "Incorrect data";
        }
        if (argc == 4)
        {
            int xp1; //размер матрицы
            int xp2; //тип заполнения
            if (toInt(argv[1], &xp1) == -1)
                throw "Incorrect data";
            if (xp1 < 1)
                throw "Incorrect data";
            if (toInt(argv[2], &xp2) == -1)
                throw "Incorrect data";
            if (xp2 == 1)
            {
                res = FillingData::FillingWithFunc1(xp1);
                flag = 1;
            }
            else if (xp2 == 2)
            {
                res = FillingData::FillingWithFunc2(xp1);
                flag = 2;
            }
            else if (xp2 == 3)
            {
                res = FillingData::FillingWithFunc3(xp1);
                flag = 3;
            }
            else
                throw "Incorrect data";
            if (toInt(argv[3], &nthreads) == -1)
                throw "Incorrect data";
        }
        if (argc == 2)
        {
            if (toInt(argv[1], &nthreads) == -1)
                throw "Incorrect data";
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
        
        //std::cout << res.first << std::endl;

        //for (int i = 0; i < res.second.size(); ++i)
        //    std::cout << res.second[i] << " ";
        //std::cout << std::endl;
        Matrix& A = res.first;
        std::cout << A << std::endl;
        std::vector<double>& b = res.second;
        //std::cout << std::endl;
        std::vector<double> x = MethodJordan::run(A, b);
        std::cout << "Solution : " << std::endl;
        size_t m = 30;
        MethodJordan::print(x, m);

        //clock_t t0 = clock();
        //double residual = MethodJordan::norm(res.first, res.second, x);
        //clock_t t1 = clock();
        //double time_seconds = (t1 - t0)/CLK_TCK;

        auto begin = std::chrono::high_resolution_clock::now();
        double residual = MethodJordan::norm(A, b, x);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Residual : " << residual << std::endl;
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
        
        double residual2 = MethodJordan::ResidualThreads(A, b, x, nthreads);
        std::cout << "Residual2 : " << residual2 << std::endl;        
        //std::vector<double> part = A.MultiplyPartOfMatrix(x, 2, 4);
        //MethodJordan::print(part, m);

        //t_full = get_full_time() - t_full;
        //if (t_full == 0)
        //    t_full = 1; /* очень быстрый компьютер... */

        //std::cout << "time : " << time_seconds << " seconds" << std::endl;

        //std::vector<double> golden_x;
        //if (flag == 1)
        //{
        //    golden_x = FillingData::GenerateX1(x.size());
        //}
        //else if (flag == 2)
        //{
        //    golden_x = FillingData::GenerateX2(x.size());
        //}
        //else if (flag == 3)
        //{
        //    golden_x = FillingData::GenerateX3(x.size());
        //}
        //else
        //{
        //    throw "Incorrect flag";
        //}
        //std::cout << MethodJordan::norm(res.first, res.second, golden_x) << std::endl;
        //double epsilon = 0.0000001;

        //double diff = FillingData::CheckAnswers(x, golden_x);
        //if (diff < epsilon)
        //{
        //    std::cout << "Answers are the same" << std::endl;
        //}
        //else
        //{
        //    std::cout << "Answers are not the same. Difference = " << diff << std::endl;
        //}
    }
    catch (char* exp)
    {
        std::cout << exp << std::endl;
    }
    
    system("pause");
    return 0;
}