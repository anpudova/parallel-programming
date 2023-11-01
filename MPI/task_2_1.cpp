#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {

    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    int count;

    const int N = 15;
    const int PART = 5;
    int a = 2;
    int b = 3;

    if (rank == 0) {
        int x[N];
        int y[N];
        int z[N];

        for (int i = 0; i < N; i++) {
            x[i] = i;
            y[i] = i + 1;
        }

        int k = 1;
        for (int i = 0; i < N; i += PART, k++) {
            MPI_Send(&x[i], PART, MPI_INT, k, 10, MPI_COMM_WORLD);
            MPI_Send(&y[i], PART, MPI_INT, k, 10, MPI_COMM_WORLD);
        }

        k = 1;
        for (int i = 0; i < N; i += PART, k++) {
            MPI_Recv(&z[i], PART, MPI_INT, k, 10, MPI_COMM_WORLD, &status);
        }

        for (int i = 0; i < N; i++) {
            printf("%d ", z[i]);
        }
    } else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);

        int x[PART];
        int y[PART];
        int z[PART];

        MPI_Recv(&x[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&y[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < count; i++) {
            z[i] = a * x[i] + b * y[i];
        }

        MPI_Send(&z, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}