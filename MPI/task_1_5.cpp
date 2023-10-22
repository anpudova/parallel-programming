#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int number = rank * 10; 

    if (rank == 0) {
        int* received_numbers = new int[size - 1]; 

        for (int source = 1; source < size; source++) {
            MPI_Recv(&received_numbers[source - 1], 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        for (int source = 1; source < size; source++) {
            std::cout << "Процесс " << source << " отправил число: " << received_numbers[source - 1] << std::endl;
        }

        delete[] received_numbers;
    } else {
        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}