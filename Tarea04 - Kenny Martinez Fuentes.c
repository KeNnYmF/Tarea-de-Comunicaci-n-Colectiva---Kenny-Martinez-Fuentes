#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int n = 4;  // tamaño de la matriz (4x4)
    int matrix[16] = {
        0,  1,  2,  3,
        4,  5,  6,  7,
        8,  9, 10, 11,
        12,13, 14, 15
    };

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0)
            printf("Este programa necesita al menos 2 procesos.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        int block_lengths[] = {4, 3, 2, 1};             // número de elementos por fila
        int displacements[] = {0, 5, 10, 15};           // desplazamientos en índices

        MPI_Datatype upper_triangle_type;
        MPI_Type_indexed(4, block_lengths, displacements, MPI_INT, &upper_triangle_type);
        MPI_Type_commit(&upper_triangle_type);

        // Enviar la parte triangular superior a proceso 1
        MPI_Send(matrix, 1, upper_triangle_type, 1, 0, MPI_COMM_WORLD);
        MPI_Type_free(&upper_triangle_type);
    }

    if (rank == 1) {
        int recv[10];  // contiene los 10 elementos del triángulo superior
        MPI_Recv(recv, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Proceso 1 recibió la parte triangular superior:\n");
        for (int i = 0; i < 10; i++) {
            printf("%d ", recv[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
