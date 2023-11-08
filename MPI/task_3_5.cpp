#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int const n = 120;
    int const part = 20;
    int x[n];
    int y[part];

    if (rank == 0) {
        printf("x: ");
        for (int i = 0; i < n; i++) {
            x[i] = i + 1;
            printf("%d ", x[i]);
        }
        printf("\n\n");
    }

    MPI_Scatter(&x[0], part, MPI_INT, &y[0], part, MPI_INT, 0, MPI_COMM_WORLD);

    int max_loc = 0;
    for (int i = 0; i < part; i++) {
        if (y[i] > max_loc) {
            max_loc = y[i];
        }
    }

    int local_result[2];
    int global_result[2];
    
    local_result[0] = max_loc;
    local_result[1] = rank;
    int result_all[size][2];
    
    MPI_Gather(local_result, 2, MPI_INT, result_all, 2, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_result, &global_result, 1, MPI_2INT, MPI_MAXLOC, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            printf("Локальный максимум процесса %d: %d\n", result_all[i][1], result_all[i][0]);
        }
        printf("Глобальный максимум: %d, процесс номер %d\n\n", global_result[0], global_result[1]);
    }

    MPI_Finalize();

    return 0;
}