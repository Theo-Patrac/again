#ifndef __SET_H
#define __SET_H

/* chaque element de la matrice de chemins.ville_suivante prend la valeur -1 */

void set_next_city (struct path ***src, short value, size_t d1, size_t d2);

/* recuperer le numero de noeud d une ville */

size_t index_in_src (char **src, const char *str, size_t size);

/* mettre une valeur pour initialiser chaque distance */

void set_distance (struct path ***src, short value, size_t d1, size_t d2);

/* changer la casse de chaque ville */

void city_case (char *str);

void alloc_and_memset_wp (weight ** w_pp, size_t s);

size_t get_index_link (size_t ics, struct path **matrix, size_t cc);
size_t get_n_of_son(size_t cc, struct path **m);

long get_weight_son(int *pred, struct path** m, size_t ics, char **cities, size_t sc);

unsigned int get_distance (size_t index_node_1, size_t index_node2, struct path **matrix);

#endif
