#include <stdio.h>
#include <omp.h>

int main() 
{
    const int N = 12;
    int a[N], b[N], c[N];

    omp_set_num_threads(3);

    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        printf("Thread %d of %d in the first parallel region.\n", thread_num, num_threads);

        #pragma omp for schedule(static)
        for (int i = 0; i < N; i++) {
            a[i] = i * 2;
            b[i] = i * 3;
        }
    }

    omp_set_num_threads(4);

    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        printf("Thread %d of %d in the second parallel region.\n", thread_num, num_threads);

        #pragma omp for schedule(dynamic)
        for (int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    printf("Array a: ");
    for (int i = 0; i < N; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");

    printf("Array b: ");
    for (int i = 0; i < N; i++) {
        printf("%d, ", b[i]);
    }
    printf("\n");

    printf("Array c: ");
    for (int i = 0; i < N; i++) {
        printf("%d, ", c[i]);
    }
    printf("\n");

    return 0;
}
