#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int TAMANO;  // Variable global para el tamaño de la matriz

// Función para reservar la memoria
int **reservar_matriz(int TAMANO) {
    int **matriz = (int **)malloc(TAMANO * sizeof(int *));
    if (matriz == NULL) exit(1);
    for (int i = 0; i < TAMANO; i++) {
        matriz[i] = (int *)malloc(TAMANO * sizeof(int));
        if (matriz[i] == NULL) exit(1);
    }
    return matriz;
}

// Función para copiar los valores a la nueva matriz
void copiar_matriz(int **origen, int **destino, int tam_origen, int tam_destino) {
    int min_tam = (tam_origen < tam_destino) ? tam_origen : tam_destino;
    for (int i = 0; i < min_tam; i++) {
        for (int j = 0; j < min_tam; j++) {
            *(*(destino + i) + j) = *(*(origen + i) + j);
        }
    }
}

// Función para llenar la matriz con valores binarios aleatorios
void llenar_matriz(int **matriz, int TAMANO, int tam_original) {
    srand(time(NULL));
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            // Solo llena las posiciones nuevas, por si el tamano aumenta
            if (i >= tam_original || j >= tam_original) {
                *(*(matriz + i) + j) = rand() % 2;
            }
        }
    }
}


void imprimir_matriz(int **matriz, int TAMANO) {
    printf("Matriz %dx%d:\n", TAMANO, TAMANO);
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            printf("%d ", *(*(matriz + i) + j));
        }
        printf("\n");
    }
}

// Función para encontrar la secuencia más larga
int encontrar_max_secuencia(int **matriz) {
    int max_secuencia = 0;
    int contador = 0;

    for (int k = 0; k < 2 * TAMANO - 1; k++) {
        int fila = (k < TAMANO) ? 0 : k - TAMANO + 1;
        int columna = (k < TAMANO) ? k : TAMANO - 1;

        while (fila < TAMANO && columna >= 0) {
            if (*(*(matriz + fila) + columna) == 1) {
                contador++;
                if (contador > max_secuencia) {
                    max_secuencia = contador;
                }
            } else {
                contador = 0;  // si encuentra un 0
            }
            fila++;
            columna--;
        }
    }

    return max_secuencia;
}

// Libera memoria
void liberar_matriz(int **matriz, int TAMANO) {
    for (int i = 0; i < TAMANO; i++) free(matriz[i]);
    free(matriz);
}

int main() {
    int diagonal_mas_larga;
    int **matriz = NULL;
    int **matriz_original = NULL;
    int tam_original;

    printf("Ingrese el tamaño inicial de la matriz cuadrada: ");
    scanf("%d", &TAMANO);
    tam_original = TAMANO;

    matriz = reservar_matriz(TAMANO);
    llenar_matriz(matriz, TAMANO, 0);  // tam_original = 0 para llenar toda la matriz
    imprimir_matriz(matriz, TAMANO);

    // Guardar una copia de la original
    matriz_original = reservar_matriz(TAMANO);
    copiar_matriz(matriz, matriz_original, TAMANO, TAMANO);

    diagonal_mas_larga = encontrar_max_secuencia(matriz);
    printf("La secuencia de 1s más grande en diagonales es: %d\n", diagonal_mas_larga);

    char opcion;
    printf("¿Quiere cambiar el tamaño de la matriz? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S') {
        int nuevo_tam;
        printf("Ingrese el nuevo tamaño: ");
        scanf("%d", &nuevo_tam);

        // Libera la matriz original y reserva una nueva
        liberar_matriz(matriz, TAMANO);
        TAMANO = nuevo_tam;
        matriz = reservar_matriz(TAMANO);

        // se copian los valores originales y se llenan los campos nuevos
        copiar_matriz(matriz_original, matriz, tam_original, TAMANO);
        llenar_matriz(matriz, TAMANO, tam_original);

        imprimir_matriz(matriz, TAMANO);
        diagonal_mas_larga = encontrar_max_secuencia(matriz);
        printf("La secuencia de 1s más grande en diagonales es: %d\n", diagonal_mas_larga);
    }

    // se libera la memoria
    liberar_matriz(matriz, TAMANO);
    liberar_matriz(matriz_original, tam_original);

    return 0;
}