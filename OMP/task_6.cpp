#include <iostream>
#include <omp.h>

int main() 
{
    const int N = 10;
    int a[N], b[N];
    
    for (int i = 0; i < N; i++) {
        a[i] = i + 1;
        b[i] = 2 * (i + 1);
    }
    
    int sum_a = 0;
    int sum_b = 0;

    #pragma omp parallel for reduction(+:sum_a,sum_b)
    for (int i = 0; i < N; i++) {
        sum_a += a[i];
        sum_b += b[i];
    }

    float avg_a = sum_a / N;
    float avg_b = sum_b / N;

    printf("Average of a = %.1f, Average of b  = %.1f \n", avg_a, avg_b);

    char sign = '=';

    if (avg_a > avg_b) {
        sign = '>';
    }

    if (avg_a < avg_b) {
        sign = '<';
    }

    printf("%.1f %c %.1f \n", avg_a, sign, avg_b);

}
