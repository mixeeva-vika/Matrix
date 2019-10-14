#include "JordanMethod.h"
#include "FillingMatrix.h"
#include<math.h>
#include <thread>
#include <mutex>

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
	if (max == 0)
	{
		throw "Singular matrix";
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

void MethodJordan::PartOfResidual(ARGS args)
{
    *(args.result) = args.thread_num;
    std::vector<double> part = args.matrix->MultiplyPartOfMatrix((*args.x), args.thread_num, args.total_threads);
    /* ѕерва€ участвующа€ строка матрицы */
    int first_row = args.matrix->size() * args.thread_num;
    first_row /= args.total_threads;
    for (int i = 0; i < part.size(); ++i)
        part[i] -= (*(args.b))[first_row + i];
    double res = 0;
    for (int i = 0; i < part.size(); ++i)
        res += part[i] * part[i];
    *(args.result) = res;
    // //t = get_time() - t;  /* врем€ конца работы */
}

std::vector<double> MethodJordan::run(Matrix& A, std::vector<double> b)
{
    Matrix M = A;
    for (size_t i = 0; i < M.size(); ++i)
    {
        size_t max_num = GetNumberMaxElem(M, i);
        if (max_num != i)
        {
            swap_row(M, i, max_num);
            swap(b[i], b[max_num]);
        }
        double max_elem = M[i][i];
		
        for (size_t j = i; j < M.size(); ++j)
        {
            double new_elem = M[i][j] / max_elem;
            M[i][j] = new_elem;
        }
        b[i] = b[i] / max_elem;

        for (size_t k = 0; k < M.size(); ++k)
        {
            if (k == i)
                continue;
            double coef = M[k][i];
            for (size_t j = i; j < M.size(); ++j)
            {
                double new_elem = M[k][j] - coef * M[i][j];
                M[k][j] = new_elem;

            }
			b[k] = b[k] - coef * b[i];
        }
    }
	std::vector<double> x(M.size());
	for (size_t i = 0; i < x.size(); ++i)
	{
		x[i] = b[i];
	}

	return x;
}

double MethodJordan::norm(const Matrix& A, const std::vector<double>& b, const std::vector<double>& x)
{
	std::vector<double> res = A * x;

    //std::cout << " A * x" << std::endl;
    //for (size_t i = 0; i < res.size(); ++i)
    //   std::cout << res[i] << " ";
    //std::cout << std::endl;

    for (size_t i = 0; i < res.size(); ++i)
        res[i] -= b[i];

	double sum = 0;
	for (size_t i = 0; i < res.size(); ++i)
		sum += res[i] * res[i];

	return sqrt(sum);
}

double MethodJordan::ResidualThreads(const Matrix& A, const std::vector<double>& b, const std::vector<double>& x, int nthreads)
{
    /* массив идентификаторов созданных задач */
    std::vector<std::thread> threads(nthreads);
    /* массив аргументов дл€ созданных задач */
    std::vector<ARGS> args(nthreads);
    std::vector<double> res(nthreads);

    /* »нициализаци€ аргументов задач */
    for (int i = 0; i < nthreads; i++)
    {
        args[i].matrix = &A;
        args[i].b = &b;
        args[i].x = &x;
        args[i].result = &res[i];
        args[i].n = A.size();
        args[i].thread_num = i;
        args[i].total_threads = nthreads;
    }
    /* «асекаем астрономическое врем€ начала работы задач*/
    //t_full = get_full_time();
    /* «апускаем задачи */
    for (int i = 0; i < nthreads; i++)
    {
        threads[i] = std::thread(MethodJordan::PartOfResidual, args[i]);
    }
    /* ќжидаем окончани€ задач */
    for (int i = 0; i < nthreads; i++)
    {
        threads[i].join();
    }

    double result = 0;
    for (int i = 0; i < nthreads; i++)
    {
        result += *(args[i].result);
    }

    return sqrt(result);
}

size_t MethodJordan::min(size_t n1, size_t n2)
{
    return (n1 > n2) ? n2 : n1;
}

void MethodJordan::print(const std::vector<double>& x, size_t m)
{
    for (size_t i = 0; i < min(m, x.size()); ++i)
        std::cout << x[i] << " ";
    std::cout << std::endl;
}





