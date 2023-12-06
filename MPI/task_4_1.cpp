#include <iostream>
#include <mpi.h>

int const n = 3000;

void ping_pong_2(int rank);
void ping_pong_1(int rank);

int main(int argc, char** argv) {

    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    ping_pong_2(rank);
    //ping_pong_1(rank);

    MPI_Finalize();
}

void ping_pong_2(int rank) {
    static int* message = new int[n];

    if (rank == 0) {

        srand(time(nullptr));

        for (int i = 0; i < n; i++) {
            message[i] = rand() % 9 + 1;
        }

        double start_time = MPI_Wtime();

        MPI_Send(message, n, MPI_INT, 1, 10, MPI_COMM_WORLD);
        MPI_Recv(message, n, MPI_INT, 1, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        double end_time = MPI_Wtime();

        float time = end_time - start_time;
        printf("Time (2 direction): %f s \n\n", time);
    }
    else {
        int* received = new int[n];

        MPI_Recv(received, n, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(received, n, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }
}


void ping_pong_1(int rank) {
    static int* message = new int[n];

    srand(time(nullptr));

    for (int i = 0; i < n; i++) {
        message[i] = rand() % 9 + 1;
    }

    double start_time;

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        start_time = MPI_Wtime();

        MPI_Send(message, n, MPI_INT, 1, 10, MPI_COMM_WORLD);
    }
    else {
        start_time = MPI_Wtime();

        MPI_Send(message, n, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        static int* received1 = new int[n];

        MPI_Recv(received1, n, MPI_INT, 1, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    }
    else {
        static int* received0 = new int[n];

        MPI_Recv(received0, n, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    float time = end_time - start_time;

    if (rank == 0) {
        printf("Time (1 direction): %f s \n\n", time);
    }
    
}