#include <mpi.h>
#include <iostream>
#include <random>

int main(int argc, char** argv) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int N = 8;

    if (rank == 0) {
        MPI_Datatype type;
        MPI_Datatype row;

        MPI_Type_contiguous(8, MPI_INT, &row);
        MPI_Type_commit(&row);
        MPI_Type_vector(4, 1, 2, row, &type);
        MPI_Type_commit(&type);
        srand(time(nullptr));

        int a[N][N];
        printf("a: \n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                a[i][j] = rand() % 9 + 1;
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        MPI_Send(&(a[1][0]), 1, type, 1, 10, MPI_COMM_WORLD);
        MPI_Send(&(a[0][0]), 1, type, 2, 10, MPI_COMM_WORLD);

    } else if (rank == 1) {

        int b[4][8];
        MPI_Recv(&(b[0][0]), 4 * 8, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("b: \n");
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                printf("%d ", b[i][j]);
            }
            printf("\n");
        }
        printf("\n");

    } else {

        int c[4][8];
        MPI_Recv(&(c[0][0]), 4 * 8, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("c: \n");
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    MPI_Finalize();

    return 0;
}