#ifndef __OUTPUT_H
#define	__OUTPUT_H

void display_input_prompt (void);	/* affichage prompt */
char *display_current_user (void);	/* affichage utilisateur courant */
void display_all_cities (char **cities, size_t size);	/* affichage des villes */

/* affichage informations liaison */

void display_informations (const char *start, const char *end, int distance);

/* affichage des chemins */

void display_matrix_of_cities (struct path **matrix, size_t d1, size_t d2);

void display_ways_informations (struct path **matrix, size_t d1, size_t d2);


void display_w_array (weight * w_p, size_t s, char **cities);

void display_predecessor(int *predecessor, char **cities, size_t size);

#endif
