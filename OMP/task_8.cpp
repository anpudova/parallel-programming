#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>

int main() 
{
    const int N = 1000; 
    std::vector<std::vector<int>> matrix(N, std::vector<int>(N));
    std::vector<int> vector(N);
    std::vector<int> result(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 100;
        }
        vector[i] = rand() % 100;
    }

    clock_t seq_start_time = clock();
    for (int i = 0; i < N; i++) {
        result[i] = 0;
        for (int j = 0; j < N; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    clock_t seq_end_time = clock();

    float seq_execution_time = static_cast<float>(seq_end_time - seq_start_time) / CLOCKS_PER_SEC;
    printf("Sequential execution time: %.5f seconds \n", seq_execution_time);

    float parall_start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        result[i] = 0;
        for (int j = 0; j < N; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    float parall_end_time = omp_get_wtime();

    float parall_execution_time = parall_end_time - parall_start_time;
    printf("Parallel execution time: %.5f seconds \n", parall_execution_time);

    return 0;
}