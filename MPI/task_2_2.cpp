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
        int b[N];
        int c[N];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = rand() % 5 + 1;
            }
            b[i] = rand() % 8 + 1;
        }

        printf("A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        printf("\nb:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", b[i]);
            printf("\n");
        }

        int n = 1;
        int j = 0;
        for (int i = 0; i < N; i+=5, n++) {
            MPI_Send(&a[i][j], PART * N, MPI_INT, n, 10, MPI_COMM_WORLD);
            MPI_Send(&b[j], N, MPI_INT, n, 10, MPI_COMM_WORLD);
        }

        n = 1;
        for (int i = 0; i < N; i+=5, n++) {
            MPI_Recv(&c[i], PART, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
        }

        printf("\nC:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", c[i]);
            printf("\n");
        }
    } else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int a[PART][N];
        int b[N];
        int c[PART];

        for (int i = 0; i < PART; i++) {
            c[i] = 0;
        }
        
        MPI_Recv(&a[0][0], PART * N, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&b[0], N, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < PART; i++) {
            for (int j = 0; j < N; j++) {
                c[i] += a[i][j] * b[j];
            }
        }
        MPI_Send(&c, PART, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
