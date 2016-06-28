#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "str.h"
#include "extern.h"

bool
check (const char *pattern, char **src, size_t size)
{
  for (size_t i = 0; i < size; i++)
    {
      if (strcmp (pattern, src[i]) == 0)
	{
	  return (true);
	}
    }

  return (false);
}

void
search (char *s)
{
  char *p = strchr (s, '\n');

  if (p)
    {
      *p = 0;
    }
  else
    {
      purge ();
    }
}

void
print (const char *str)
{
  for (size_t i = 0; str[i] != '\0'; i++)
    write (STDOUT_FILENO, &str[i], sizeof (char));
}

size_t
c_count (const char *str, int c)
{
  size_t count;

  count = 0;

  if (str == NULL)
    return (count);
  else
    {
      for (size_t i = 0; i < strlen (str); i++)
	{
	  if (str[i] == c)
	    {
	      count++;
	    }
	}
    }
  return (count);
}
