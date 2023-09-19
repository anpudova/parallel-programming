#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

int main() 
{
    srand(time(nullptr));

    int d[6][8];
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            d[i][j] = rand() % 100;
        }
    }

    float avg = 0.0;
    
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int thread_id = omp_get_thread_num();
            float sum = 0.0;
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 8; ++j) {
                    sum += d[i][j];
                }
            }
            avg = sum / (6 * 8);
            printf("Thread %d : Average value = %.1f \n", thread_id, avg);
        }

        #pragma omp section
        {
            int thread_id = omp_get_thread_num();
            int min_val = d[0][0];
            int max_val = d[0][0];
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (d[i][j] < min_val) {
                        min_val = d[i][j];
                    }
                    if (d[i][j] > max_val) {
                        max_val = d[i][j];
                    }
                }
            }
            printf("Thread %d : Min value = %d, Max value = %d \n", thread_id, min_val, max_val);
        }

        #pragma omp section
        {
            int thread_id = omp_get_thread_num();
            int count = 0;
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (d[i][j] % 3 == 0) {
                        count++;
                    }
                }
            }
            printf("Thread %d : Number of elements div 3 = %d \n", thread_id, count);
        }
    }

    return 0;
}
