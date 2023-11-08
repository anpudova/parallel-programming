#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int N = 120;
    const int part = 20;

    int b[N];
    int a[N][N];
    int a_part[part][N];

    srand(time(nullptr));

    if (rank == 0) {
        for (int i = 0; i < N; ++i) {
            b[i] = i;
            for (int j = 0; j < N; ++j) {
                a[i][j] = rand() % 5 + 1;
            }
        }

        printf("A: \n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");

        printf("b : ");
        for (int i = 0; i < N; ++i) {
            printf("%d ", b[i]);
        }
        printf("\n\n");

        
    }

    MPI_Bcast(b, N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(a, part * N, MPI_INT, a_part, part * N, MPI_INT, 0, MPI_COMM_WORLD);

    int result[part];

    for (int i = 0; i < part; i++) {
        result[i] = 0;
        for (int j = 0; j < N; j++) {
            result[i] += a_part[i][j] * b[j];
        }
    }

    int result_all[N];

    MPI_Gather(result, part, MPI_INT, result_all, part, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result: ");
        for (int i = 0; i < N; ++i) {
            printf("%d ", result_all[i]);
        }
        printf("\n");
    }

    MPI_Finalize();

    return 0;
}