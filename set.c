#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "macro.h"
#include "struct.h"
#include "set.h"
#include "lifo.h"

void
set_next_city (struct path ***src, short value, size_t d1, size_t d2)
{
  for (size_t i = 0; i < d1; i++)
    for (size_t j = 0; j < d2; j++)
      (*src)[i][j].next_city = value;
}

void
set_distance (struct path ***src, short value, size_t d1, size_t d2)
{
  value = 0;

  for (size_t i = 0; i < d1; i++)
    for (size_t j = 0; j < d2; j++)
      (*src)[i][j].distance = value;
}

size_t
index_in_src (char **src, const char *str, size_t size)
{
  size_t index;

  index = 0;

  for (size_t i = 0; i < size; i++)
    {
      if (strcmp (src[i], str) == 0)
	{
	  index = i;
	}
    }

  return (index);
}

/*
	pour eviter les problemes, de sensibilite a la casse, on met toutes les entrees
	a la casse suivante :
		premiere lettre en majscule,
		le reste en minuscule.
*/

void
city_case (char *str)
{
  str[0] = toupper (str[0]);

  for (size_t i = 1; i < strlen (str); i++)
    {
      str[i] = tolower (str[i]);
    }
}

void
alloc_and_memset_wp (weight ** w_pp, size_t s)
{
  *w_pp = malloc (sizeof (**w_pp) * s);

  if (!w_pp)
    {
      perror ("malloc");
      exit (1);
    }

  /* on fait un memset de la structure */

  for (size_t i = 0; i < s; i++)
    {
      (*w_pp)[i].node = i;
      (*w_pp)[i].weight = -1;
      (*w_pp)[i].check = false;
    }
}

size_t
get_index_link (size_t ics, struct path **matrix, size_t cc)
{
  size_t index;

  for (size_t i = 0; i < N_OF_PATH_MAX; i++)
    {
      if (matrix[cc][i].next_city == ics)
	{
	  index = i;
	}
    }

  return (index);
}

size_t get_n_of_son(size_t cc, struct path **m)
{
	size_t n_of_son;

	n_of_son = 0;

	for(size_t i = 0; i < N_OF_PATH_MAX; i++)
	{
		if(m[cc][i].next_city != -1)
		{
			n_of_son++;
		}
	}

	return (n_of_son);
}

long get_weight_son(int *pred, struct path** m, size_t ics, char **cities, size_t sc)
{
	int res;
	long weight;

	weight = 0;
	res = ics;

	printf("poid de %s:", cities[ics]);

	while(res != -1)
	{
		if(pred[res] == -1)
		{
			printf("%s ", cities[sc]);	
		}
		printf("%s ", cities[res]);
		
		res = pred[res];
	}

	puts("");

	return(weight);
}


unsigned int get_distance (size_t index_node_1, size_t index_node2, struct path **matrix)
{
	unsigned int	distance;

	for(size_t i = 0; i < N_OF_PATH_MAX; i++)
	{
		if(matrix[index_node_1][i].next_city == index_node2)
		{
			distance = matrix[index_node_1][i].distance;
			break;
		}
	}

	return (distance);
}
