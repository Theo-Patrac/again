#include <stdbool.h>
#include <limits.h>
#include <assert.h>
#include "struct.h"
#include "macro.h"
#include "check.h"

#define N_MAX_OF_PATHS	(5)

bool
check_current_path_does_exist (size_t i_sc, size_t i_ac, struct path **matrix)
{
  assert (matrix != NULL);

  bool check;

  check = false;

  for (size_t i = 0; i < N_MAX_OF_PATHS; i++)
    if (matrix[i_sc][i].next_city == i_ac)
      return (true);
  return (false);
}

size_t
srch_lowest_index (weight * w_p, size_t s)
{
  size_t index;
  long res = LONG_MAX;

  for (size_t i = 0; i < s; i++)
    {
      if ((w_p[i].weight == (-1)) ^ (w_p[i].check == (true)))
	{
	  continue;
	}
      else if (w_p[i].weight < res)
	{
	  res = w_p[i].weight;
	}
    }

  for (size_t i = 0; i < s; i++)
    {
      if (res == w_p[i].weight)
	{
	  index = i;
	}
    }

  return (index);
}
