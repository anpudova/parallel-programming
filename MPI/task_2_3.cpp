#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {

    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    int count;

    srand(time(nullptr));
    const int N = 15;
    const int PART = 5;

    if (rank == 0) {
        int a[N][N];
        int b[N][N];
        int c[N][N];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = rand() % 5 + 1;
                b[i][j] = rand() % 8 + 1;
            }
        }

        printf("A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        printf("\nB:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", b[i][j]);
            }
            printf("\n");
        }

        int n = 1;
        int j = 0;
        for (int i = 0; i < N; i+=5, n++) {
            MPI_Send(&a[i][j], PART * N, MPI_INT, n, 10, MPI_COMM_WORLD);
            MPI_Send(&b[i][j], PART * N, MPI_INT, n, 10, MPI_COMM_WORLD);
        }

        n = 1;
        for (int i = 0; i < N; i+=5, n++) {
            MPI_Recv(&c[i][j], PART * N, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
        }

        printf("\nC:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
    } else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int a[PART][N];
        int b[PART][N];
        int c[PART][N];

        MPI_Recv(&a[0][0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&b[0][0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < PART; i++) {
            for (int j = 0; j < N; j++) {
                c[i][j] = a[i][j] * b[i][j];
            }
        }
        MPI_Send(&c, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}