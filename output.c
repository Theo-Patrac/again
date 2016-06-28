#ifdef __WIN32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "struct.h"
#include "macro.h"
#include "output.h"
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"
#include "macro.h"
#include "output.h"
#include "extern.h"
#endif

void
display_input_prompt (void)
{
#ifdef __WIN32
  printf ("[%s]>>>", getenv ("USERNAME"));	/* Windows prompt */
#else
  printf ("[%s]>>>", getenv ("USER"));	/* Linux prompt */
#endif
}

void
display_informations (const char *start, const char *end, int distance)
{
  printf ("[1] Ville de depart:%s.\n"
	  "[2] Ville d'arrivee:%s.\n"
	  "[3] Distance:%d km.\n", start, end, distance);
}

char *
display_current_user (void)
{
#ifdef __WIN32
  return (getenv ("USERNAME"));	/* running on Windows shell */
#else
  return (getenv ("USER"));	/* running on Linux shell */
#endif
}

void
display_all_cities (char **cities, size_t size)
{
  if (cities != NULL)
    for (size_t i = 0; i < size; i++)
      {
	printf ("Ville numero %" PRIsz ":%s\n", i, cities[i]);
      }
  else
    {
      fprintf (stderr, "Vous n'avez pas encore saisie les villes.\n");
    }
}

void
display_matrix_of_cities (struct path **matrix, size_t d1, size_t d2)
{
  for (size_t i = 0; i < d1; i++)
    for (size_t j = 0; j < d2; j++)
      printf ("chemin[%" PRIsz "][%" PRIsz "].next_city=%d\n",
	      i, j, matrix[i][j].next_city);
}

void
display_ways_informations (struct path **matrix, size_t d1, size_t d2)
{
  for (size_t i = 0; i < d1; i++)
    for (size_t j; j < d2; j++)
      printf ("ville[%" PRIsz "][%" PRIsz "].suivante=%d | "
	      "ville[%" PRIsz "][%" PRIsz "].distance=%d\n", i,
	      j, matrix[i][j].next_city, i, j, matrix[i][j].distance);
}

void
display_w_array (weight * w_p, size_t s, char **cities)
{
  puts ("\nAffichage du tableau des poids:");
  printf ("%16s%7s%7s%13s\n\n", "nom du noeud", "index", "poid", "deja parcouru");

  for (size_t i = 0; i < s; i++)
    {
      printf ("%15s|%6zu|%6ld|%13d\n", cities[i], w_p[i].node, w_p[i].weight, w_p[i].check);

      sleep (1);
    }

}

void
display_predecessor(int *predecessor, char **cities, size_t size)
{
	puts("\nAffichage des predecesseurs:");
	
	for(size_t i = 0; i < size; i++)
	{
		if(predecessor[i] != -1)
		{
			printf("predecesseur(%s)=%s.\n"
			, cities[i], cities[predecessor[i]]);
		}
		else
		{
			printf("La ville %s n'a pas de predecesseur\n", cities[i]);
		}

	}
}
