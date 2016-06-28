#ifndef	__INPUT_H
#define	__INPUT_H

char *input_starting_city (char *s, char **src, size_t size);	/* saisie ville de dep */
char *input_arrival_city (char *, char **, char *, size_t);	/* saisie ville arrivee */
int input_distance (void);	/* saisie distance */
void user_input_cities (char ***src, size_t size);	/* saisie des villes */
void user_input_n_of_cities (short *n);	/* saisie du nombre de villes */
void input_cities (char ***p, size_t n);
struct route distance (char **cities, size_t size);	/* saisie distance */
void get_route (char **cities, size_t size, struct path **matrix);	/* recuperer chemin */

#endif /*input.h inclued */
