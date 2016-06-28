#ifndef __MEMORY_H
#define __MEMORY_H

#include "struct.h"

bool alloc_cities (char ***cities, size_t n_of_cities);	/* allocation villes */
void alloc_path (struct path ***p, size_t d1, size_t d2);	/* allocation matrice de chemins */
void free_cities (char ***p, size_t d1);	/* free des villes */
void free_matrix_path (struct path ***p, size_t size);	/* free matrice de chemins */
bool c_type_alloc_and_debug_1D (char **src, size_t size);
struct path **alloc_matrix_of_path (size_t d1, size_t d2);
void free_matrix_of_path (struct path ***p, size_t size);
void alloc_c (char **c);
void free_c (char **c);

#endif /* memory.h inclued */
