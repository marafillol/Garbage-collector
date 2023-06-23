#include <stdio.h>
#include <string.h>
#include "garbage.h"


int main() {
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
    printf("Memoria disponible: %d\n", available_memory());
    
    // Prueba de destroy_agent
    destroy_agent();

    return 0;
}
