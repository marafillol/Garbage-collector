#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "garbage.h"

int* tamanio; // Puntero a un entero para almacenar el tamaño de los bloques
char** nombres_de_bloque; // Puntero a un puntero a caracteres para almacenar los nombres de los bloques
int* referencias; // Puntero a un entero para almacenar las referencias de los bloques
int cant_bloques; // Variable entera para contar la cantidad de bloques existentes
int identificador; // Variable entera para asignar identificadores únicos a los bloques (inicializada en 0)

int memoria_total; // Variable entera para almacenar la memoria total del sistema
int memoria_utilizada; // Variable entera para almacenar la memoria utilizada en el sistema

int init_gc(int max_mem) { // Función para inicializar los arreglos, la memoria y las variables del sistema.
    memoria_total = max_mem; // Asigna el valor máximo de memoria recibido como parámetro
    int *tamanio = NULL; // Inicializa el puntero a tamaño como NULL
    referencias = NULL; // Inicializa el puntero a referencias como NULL
    nombres_de_bloque = NULL; // Inicializa el puntero a nombres_de_bloque como NULL
    cant_bloques = 0; // Inicializa la cantidad de bloques en 0
    identificador = 0; // Inicializa el identificador en 0
    memoria_utilizada = 0; // Inicializa la memoria utilizada en 0
}

int new_block(int sz, char* name) { // Función para asignar el tamanio, nombre e identificador a cada bloque.
    tamanio = realloc(tamanio, (cant_bloques + 1) * sizeof(int)); // Realiza realloc para el arreglo tamanio, aumentando su tamanio en 1
    nombres_de_bloque = realloc(nombres_de_bloque, (cant_bloques + 1) * sizeof(char*)); // Realiza realloc para el arreglo nombres_de_bloque, aumentando su tamanio en 1
    referencias = realloc(referencias, (cant_bloques + 1) * sizeof(int)); // Realiza realloc para el arreglo referencias, aumentando su tamanio en 1

    int largo_de_nombre = strlen(name) + 1; // Variable para indicar la longitud del nombre del bloque
    nombres_de_bloque[cant_bloques] = malloc(largo_de_nombre * sizeof(char)); // Asigna memoria para el nombre del bloque


    tamanio[cant_bloques] = sz; // Asigna el tamanio del bloque en el arreglo tamanio
    referencias[cant_bloques] = 0; // Inicializa las referencias del bloque en 0

    cant_bloques++; // Incrementa la cantidad de bloques
    identificador++; // Incrementa el identificador

    memoria_utilizada += sz; // Actualiza la memoria utilizada sumando el tamaño del bloque

    printf("Nuevo bloque \"%s\" creado con tamanio %d\n", name, sz); // Imprime un mensaje indicando la creación del bloque

    return identificador; // Devuelve el identificador del bloque
}

int resize(int block, int sz) { // Función para redimensionar el tamanio de los bloques y actualizar la memoria.
    if (block < 1 || block > cant_bloques) { // Verifica si el identificador del bloque es inválido
        printf("El identificador del bloque es inválido.\n");
        return -1;
    }

    int i = block - 1; // Obtiene el índice del bloque en los arreglos (resta 1 al identificador)

    int tamanio_viejo = tamanio[i]; // Obtiene el tamanio actual del bloque

    int diff = sz - tamanio_viejo; // Calcula la diferencia de tamaño

    if (memoria_total - (memoria_utilizada - tamanio_viejo) + sz < 0) { // Verifica si hay suficiente memoria disponible para un nuevo tamanio de bloque
        printf("No hay suficiente memoria disponible para redimensionar el bloque.\n");
        return -1;
    }

    memoria_utilizada = memoria_utilizada - tamanio_viejo + sz; // Actualiza la memoria utilizada

    tamanio[i] = sz; // Actualiza el tamanio del bloque

    printf("El bloque %d ha sido redimensionado correctamente. Nuevo tamanio: %d\n", block, sz); // Imprime un mensaje indicando el redimensionamiento

    return sz; // Devuelve el nuevo tamanio del bloque
}

int add_reference(int block) { // Función para agregar referencias a los bloques.
    if (block < 1 || block > cant_bloques) { // Verifica si el identificador del bloque es inválido
        printf("El identificador del bloque es inválido.\n");
        return -1;
    }

    int i = block - 1; // Obtiene el índice del bloque en los arreglos

    referencias[i]++; // Incrementa el contador de referencias

    printf("Referencia agregada al bloque %d\n", block); // Imprime un mensaje indicando la adición de una referencia

    return referencias[i]; // Devuelve la cantidad actualizada de referencias del bloque
}

int remove_reference(int block) { // Función para remover referencias de los bloques.
    if (block < 1 || block > cant_bloques) { // Verifica si el identificador del bloque es inválido
        printf("El identificador del bloque es inválido.\n");
        return -1;
    }

    int i = block - 1; // Obtiene el índice del bloque en los arreglos

    if (referencias[i] <= 0) { // Verifica si el bloque no tiene referencias antes de decrementar
        printf("El bloque no tiene referencias.\n");
        return -1;
    }

    referencias[i]--; // Decrementa el contador de referencias

    printf("Referencia removida del bloque %d\n", block); // Imprime un mensaje indicando la eliminación de una referencia

    return referencias[i]; // Devuelve la cantidad actualizada de referencias del bloque
}

int used_memory() { // Función para obtener la cantidad de memoria utilizada
    int total = 0;

    for (int i = 0; i < cant_bloques; i++) {
        total += tamanio[i]; // Suma el tamanio de cada bloque
    }

    return total; // Devuelve la cantidad total de memoria utilizada
}

int available_memory() { // Función para obtener la cantidad de memoria disponible
    return memoria_total - used_memory(); // Resta la memoria utilizada a la memoria total
}

void destroy_agent() { // Función para liberar la memoria utilizada y reinicializar las variables y arreglos
    for (int i = 0; i < cant_bloques; i++) {
        free(nombres_de_bloque[i]); // Libera la memoria asignada para cada nombre de bloque
    }

    free(tamanio); // Libera la memoria asignada para el arreglo de tamanios
    free(referencias); // Libera la memoria asignada para el arreglo de referencias
    free(nombres_de_bloque); // Libera la memoria asignada para el arreglo de nombres de bloque

    cant_bloques = 0; // Reinicializa la cantidad de bloques a 0
    identificador = 0; // Reinicializa el identificador a 0
    memoria_utilizada = 0; // Reinicializa la memoria utilizada a 0

    printf("Agente de garbage collector destruido.\n"); 
}

int main() { // caso de prueba 
    int max_mem = 1000;
    int block1, block2, block3, block4;

    // Prueba de init_gc
    init_gc(max_mem);

    // Prueba de new_block
    block1 = new_block(200, "Block 1");
    block2 = new_block(300, "Block 2");
    block3 = new_block(150, "Block 3");
    block4 = new_block(400, "Block 4");

    // Prueba de resize
    resize(block2, 400);
    resize(block4, 250);

    // Prueba de add_reference
    add_reference(block1);
    add_reference(block2);
    add_reference(block2); // Agregar dos referencias al mismo bloque
    add_reference(block3);

    // Prueba de remove_reference
    remove_reference(block2);
    remove_reference(block2); // Quitar una referencia más al mismo bloque

    // Prueba de used_memory
    int used_mem = used_memory();
    printf("Memoria en uso: %d\n", used_mem);

    // Prueba de available_memory
    int available_mem = available_memory();
    printf("Memoria disponible: %d\n", available_mem);

    // Prueba de destroy_agent
    destroy_agent();

    return 0;
}
