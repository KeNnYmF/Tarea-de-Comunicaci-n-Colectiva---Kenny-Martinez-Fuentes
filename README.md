# Tarea de Comunicación Colectiva - Kenny Martinez Fuentes

Este proyecto corresponde a la **Tarea de Comunicación Colectiva** desarrollada en el curso, cuyo objetivo es implementar un programa en C que utilice MPI para enviar y recibir datos entre procesos.

## Descripción

El programa crea una matriz de 4x4 con valores enteros y utiliza MPI para comunicar información entre dos procesos:

- El **proceso 0** crea un tipo de dato derivado que representa la parte triangular superior de la matriz (los elementos por encima y en la diagonal principal).
- Este proceso envía esa parte triangular al **proceso 1**.
- El **proceso 1** recibe los datos y los imprime en pantalla.

La comunicación se realiza usando funciones básicas de MPI (`MPI_Send` y `MPI_Recv`) junto con la definición de un tipo derivado con `MPI_Type_indexed` para seleccionar los elementos específicos de la matriz que se desean enviar.

## Requisitos

- Tener instalado MPI (por ejemplo, OpenMPI o MPICH).
- Un compilador compatible con C.
- Ejecutar con al menos 2 procesos.

## Cómo compilar y ejecutar

```bash
mpicc -o tarea tarea.c
mpirun -np 2 ./tarea
