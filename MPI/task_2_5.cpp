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
        int transp_a[N][N];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = rand() % 5 + 1;
            }
        }

        printf("A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        int n = 1;
        int j = 0;
        int temp_a[N][PART];
        for (int i = 0; i < N; i+=PART, n++) {
            for (int k = 0; k < N; k++) {
                for (int g = 0; g < PART; g++) {
                    temp_a[k][g] = a[k][g + PART * (n - 1)];
                }
            }
            MPI_Send(&temp_a[j][j], PART * N, MPI_INT, n, 10, MPI_COMM_WORLD);
        }

        n = 1;
        for (int i = 0; i < N; i+=PART, n++) {
            MPI_Recv(&transp_a[i][j], PART * N, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
        }

        printf("\nTransp A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", transp_a[i][j]);
            }
            printf("\n");
        }
    } else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int a[N][PART];
        int transp_a[PART][N];
        
        for (int i = 0; i < PART; i++) {
            for (int j = 0; j < N; j++) {
                transp_a[i][j] = 0;
            }
        }

        MPI_Recv(&a[0][0], PART * N, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < PART; i++) {
            for (int j = 0; j < N; j++) {
                transp_a[i][j] = a[j][i];
            }
        }
        MPI_Send(&transp_a, PART * N, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}