#include <stdio.h>
#include <omp.h>

int fib_calc(int num)
{
    if (num <= 1)
        return num;

    int a, b;
#pragma omp task shared(a)
    a = fib_calc(num - 1);

#pragma omp task shared(b)
    b = fib_calc(num - 2);

#pragma omp taskwait
    return a + b;
}

int main()
{
    int num = 10;
    int fib_result;
#pragma omp parallel
    {
#pragma omp single
        {
            fib_result = fib_calc(num);
        }
    }
    printf("Fibonacci of %d numbers is = %d\n", num, fib_result);
    return 0;
}
