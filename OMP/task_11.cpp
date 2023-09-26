#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int main() 
{
    const int size = 100;
    int a[size];

    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        a[i] = rand() % 100;
    }

    int max_value = -1;

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        if (a[i] % 7 == 0 && a[i] > max_value) {
            #pragma omp critical
            {
                max_value = a[i];
            }
        }
    }

    if (max_value == -1) {
        printf("No maximum value divisible by 7 \n");
    } else {
        printf("Maximum value divisible by 7: %d \n", max_value);
    }

    return 0;
}
