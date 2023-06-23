#define OK 0
#define ERROR (-1)
//Inicializacion del GC. Se indica cantidad de memoria.
int init_gc(int max_mem);
//Creacion de un nuevo bloque de memoria.
int new_block(int sz,char* nombre);
//Redimensionamiento de memoria.
int resize(int block, int sz);
//Se agrega una referencia a un bloque de memoria existente.
int add_reference(int block);
//Se elimina una referencia a un bloque de memoria.
int remove_reference(int block);
//Calcula cuanta memoria queda
int used_memory(void);
//Calcula cuanta memoria queda disponible.
int available_memory(void);
//Destructor del GC.
void destroy_agent(void);
