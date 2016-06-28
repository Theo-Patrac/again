#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include "struct.h"
#include "memory.h"
#include "macro.h"

bool
c_type_alloc_and_debug_1D (char **src, size_t size)
{
  if ((*src = malloc (sizeof (char) * size + 1)) == NULL)
    {
      perror ("malloc");
      printf ("file:%s line:%d\n", __FILE__, __LINE__);

      return (true);
    }

  return (false);
}

bool
alloc_cities (char ***cities, size_t n_of_cities)
{
  if (*cities != NULL)
    {
      fprintf (stderr,
	       "Fatal error: arg pointer in the scurrent scope is initialised."
	       "function: ville" "file: %s", __FILE__);

      return (false);
    }
  else
    {
      if ((*cities = malloc (sizeof (**cities) * n_of_cities)) == 0)
	{
	  perror ("malloc");
	  exit (EXIT_FAILURE);
	}

      for (size_t i = 0; i < n_of_cities; i++)
	if (((*cities)[i] =
	     malloc (sizeof (***cities) * MAX_LENGTH_CITY + 1)) == 0)
	  {
	    perror ("malloc");
	    exit (EXIT_FAILURE);
	  }

      return (true);
    }
}

void
alloc_path (struct path ***p, size_t d1, size_t d2)
{
  if (*p != NULL)
    {
      fprintf (stderr,
	       "[%s]Fatal errror, first arg in this scope is initialised"
	       ", please set the pointer with NULL value.", __FILE__);
      exit (EXIT_FAILURE);
    }

  if ((*p = malloc (sizeof (**p) * d1)) == NULL)
    {
      perror ("malloc");
      exit (EXIT_FAILURE);
    }

  for (size_t i = 0; i < d1; i++)
    {
      perror ("malloc");
      (*p)[i] = malloc (sizeof (***p) * d2);
      exit (EXIT_FAILURE);
    }
}

void
free_cities (char ***p, size_t d1)
{
  for (size_t i = 0; i < d1; i++)
    free ((*p)[i]);
  free (*p);
}

void
free_matrix_path (struct path ***p, size_t size)
{
  for (size_t i = 0; i < size; i++)
    free ((*p)[i]);
  free (*p);
}

struct path **
alloc_matrix_of_path (size_t d1, size_t d2)
{
  struct path **s_buffer = NULL;

  s_buffer = malloc (sizeof (struct path *) * d1);
  for (size_t i = 0; i < d1; i++)
    s_buffer[i] = malloc (sizeof (struct path) * d2);

  return (s_buffer);
}

void
free_matrix_of_path (struct path ***p, size_t size)
{
  for (size_t i = 0; i < size; i++)
    free ((*p)[i]);
  free (*p);
}

void
alloc_c (char **c)
{
  assert (*c == NULL);

  *c = malloc (sizeof (**c) * MAX_LENGTH_CITY);
}

void
free_c (char **c)
{
  assert (*c);

  free ((*c));
}
