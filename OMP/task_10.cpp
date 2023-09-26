#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int main() 
{
    const int size = 30;
    int a[size];

    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        a[i] = rand() % 100; 
    }

    int count = 0; 

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        if (a[i] % 9 == 0) {
            #pragma omp atomic
            count++;
        }
    }

    printf("Number of elements divisible by 9: %d \n", count);

    return 0;
}