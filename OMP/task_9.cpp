#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int main() 
{
    const int rows = 6;
    const int cols = 8;
    int d[rows][cols];

    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            d[i][j] = rand() % 100; 
        }
    }

    int min_value = d[0][0]; 
    int max_value = d[0][0]; 

    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            #pragma omp critical
            if (d[i][j] < min_value) {
                min_value = d[i][j];
            }

            #pragma omp critical
            if (d[i][j] > max_value) {
                max_value = d[i][j];
            }
        }
    }

    printf("Min value: %d \nMax value: %d \n", min_value, max_value);

    return 0;
}