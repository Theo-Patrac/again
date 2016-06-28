#ifdef __WIN32
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include "input.h"
#include "output.h"
#include "str.h"
#include "memory.h"
#include "macro.h"
#include <wchar.h>
#include "set.h"
#include "check.h"
#else /* POSIX SYSTEM */
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include "input.h"
#include "output.h"
#include "str.h"
#include "memory.h"
#include "macro.h"
#include "set.h"
#include "check.h"
#endif

void
user_input_n_of_cities (short *n)
{
  char buffer[MAX_LENGTH_BUFFER];
  int res;
  bool error_input = false;

  while (1)
    {
      if (error_input == true)
	{
	  fprintf (stderr, "Erreur de lecture du nombre de ville\n"
		   "Saisir un entier entre 2 et 20.\n");
	}

      puts ("Saisir le nombre de ville.");
      display_input_prompt ();
      fgets (buffer, 3, stdin);
      search (buffer);
      res = sscanf (buffer, "%2hd", n);

      if (res == 1 && bad_input_cities (*n) == 0)
	break;
      error_input = true;
    }

  printf ("Votre choix: %hd ville(s).\n", *n);
}

void
input_cities (char ***p, size_t n)
{
  for (size_t i = 0; i < n; i++)
    {
      printf ("Saisir la ville [%" PRIsz "]>", i);
      fgets ((*p)[i], MAX_LENGTH_CITY - 1, stdin);
      (*p)[i][0] = 'X';
    }
}

struct route
distance (char **cities, size_t size)
{
  struct route itinerary;
  int distance;
  char *starting_city = NULL;
  char *city_of_arrival = NULL;

  if (c_type_alloc_and_debug_1D (&starting_city, MAX_LENGTH_CITY) == true)
    exit (EXIT_FAILURE);	//allocation échouée ville de départ
  if (c_type_alloc_and_debug_1D (&city_of_arrival, MAX_LENGTH_CITY) == true)
    exit (EXIT_FAILURE);	//allocation échouee ville d'arrivée

  starting_city = input_starting_city (starting_city, cities, size);
  city_case (starting_city);
  city_of_arrival = input_arrival_city (city_of_arrival,
					cities, starting_city, size);
  city_case (city_of_arrival);

  distance = input_distance ();
  display_informations (starting_city, city_of_arrival, distance);

  itinerary.index_of_starting_city =
    index_in_src (cities, starting_city, size);
  itinerary.index_of_arrival_city =
    index_in_src (cities, city_of_arrival, size);
  itinerary.distance = distance;

  free (starting_city);
  free (city_of_arrival);

  return (itinerary);
}

char *
input_starting_city (char *s, char **src, size_t size)
{
  print ("Saisir la ville de depart>>>");
  bool _check = false;

  while (1)
    {
      fgets (s, MAX_LENGTH_CITY, stdin);
      city_case (s);
      search (s);

      if ((_check = check (s, src, size)) == false)
	fprintf (stderr, "La ville n'est pas referencee\n"
		 "Saisir une autre ville>>>");
      else
	break;
    }
  return (s);
}

char *
input_arrival_city (char *city_of_arrival, char **cities,
		    char *starting_city, size_t size)
{
  print ("Saisir la ville d'arrivee>>>");

  while (1)
    {
      bool _check = false;
      fgets (city_of_arrival, MAX_LENGTH_CITY, stdin);
      city_case (city_of_arrival);
      search (city_of_arrival);

      if ((_check = check (city_of_arrival, cities, size)) == false)
	fprintf (stderr, "La ville n'est pas referencee\n"
		 "Saisir une autre ville>>>");
      else if (strcmp (starting_city, city_of_arrival) == 0)
	fprintf (stderr,
		 "Erreur: La ville de depart est la meme, "
		 "que la ville d'arrivee.\n" "Saisir une autre ville>>>");
      else
	break;
    }

  return (city_of_arrival);
}

int
input_distance (void)
{
  char buffer[19];
  int distance;

  while (1)
    {
      print ("Saisir la distance>>>");
      fgets (buffer, 18, stdin);
      search (buffer);
      if (sscanf (buffer, "%d", &distance) == 1
	  && bad_input_distance (distance) == 0)
	break;
      else
	fprintf (stderr, "Erreur de saisie\n"
		 "Saisir une valeur entre 0 et 20 000\n");
    }

  return (distance);
}

void
user_input_cities (char ***src, size_t size)
{
  for (size_t i = 0; i < size; i++)
    {
      printf ("Saisir la ville numero %" PRIsz ">>>", i + 1);
      fgets ((*src)[i], MAX_LENGTH_CITY, stdin);
      search ((*src)[i]);

      if (is_strictly_positive (i) == 1 && check ((*src)[i], *src, i) == true)
	{
	  bool code;

	  do
	    {
	      fprintf (stderr,
		       "Cette ville est deja referencee.\n"
		       "Saisir une autre ville>>>");
	      fgets ((*src)[i], MAX_LENGTH_CITY, stdin);
	      search ((*src)[i]);
	      code = check ((*src)[i], *src, i);
	    }
	  while (code == true);
	}
    }
}

void
get_route (char **cities, size_t size, struct path **matrix)
{
  char sc[20];			/* ville de depart */
  char ac[20];			/* ville d'arrivee */
  size_t index_sc;		/* index ville de depart */
  size_t index_ac;		/* index ville arrivee */
  bool check_memory;
  size_t i;
  char confirmation;

  printf ("Saisir la ville de depart>>>");

  while (1)
    {
      fgets (sc, sizeof (sc) - 1, stdin);
      city_case (sc);
      search (sc);

      if (strcmp (sc, "99") == 0)
	return;
      else if (check (sc, cities, size) == false)
	fprintf (stderr, "La ville n'est pas referencee\n"
		 "Saisir une autre ville>>>");
      else
	break;
    }

  printf ("Saisir la ville de d'arrivee>>>");

  while (1)
    {
      fgets (ac, sizeof (ac) - 1, stdin);
      city_case (ac);
      search (ac);

      if (strcmp (ac, "99") == 0)
	{
	  fprintf (stderr, "Vous quittez la fonction: %s", __func__);
	  return;
	}
      else if (check (ac, cities, size) == false)
	fprintf (stderr, "La ville n'est pas referencee\n"
		 "Saisir une autre ville>>>");
      else
	break;
    }

  index_sc = index_in_src (cities, sc, size);
  index_ac = index_in_src (cities, ac, size);

  check_memory = false;

  for (i = 0; i < 5; i++)
    {
      if ((size_t) matrix[index_sc][i].next_city == index_ac)
	{
	  check_memory = true;
	  break;
	}
      else
	continue;
    }

  if (check_memory == true)
    {
      printf ("Distance %s-%s=%d km.\n", sc, ac,
	      (int) matrix[index_sc][i].distance);
    }
  else
    {
      fputs ("Erreur de lecture de la distance.", stderr);
      return;
    }
}
