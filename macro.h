#ifndef __MACRO_H
#define __MACRO_H

#ifdef __WIN32			/* portabilité pour affichage formaté objet de type size_t */
#define PRIsz "Iu"		/* pour les environnements Windows */
#else
#define PRIsz "zu"		/* pour les systemes POSIX */
#endif

#ifdef __linux__
#define clrscr() 			printf("\033[H\033[2J")	/* ecrit sur le FILE* stdout
								   efface l'output */
#endif

#define is_strictly_positive(x)         ((x) >= 1 ? (1) : (0))
#define bad_input_cities(n)             (((n) <= (1)) ^ ((n) > 20) ? (1) : (0))
#define bad_input_distance(d)           (((d) <= 0) ^ ((d) > 20000) ? (1): (0))

#define MAX_LENGTH_LINE			(256)
#define MAX_LENGTH_CMD          	(500)	/* long max commande */
#define N_MAX_OF_CITIES         	(20)	/* nombre de villes max */
#define MAX_LENGTH_BUFFER		(5)	/* long max buffer */
#define MAX_LENGTH_CITY			(20)	/* long max nom de ville */
#define GOOD_INPUT			(1)
#define	EXIT_FUNCTION			"99"
#define SPACE				(32)	/* code ascii <space> */
#define N_OF_PATH_MAX			(5)	/* nombre de chemins max partant d une ville */
#define NO_PREDECESSOR			(99)
#define	display_separation_of_row()	printf("+----------------------------");\
					printf("--------------------------+\n");

#endif
