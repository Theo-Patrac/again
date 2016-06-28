#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include "extern.h"

void
purge (void)
{				/* purge de stdin */
  int c;

  while ((c = getchar ()) != '\n' && c != EOF);
}

pid_t
create_process (void)
{				/* creation de processus sous system POSIX */
  pid_t pid;

  while (((pid = fork ()) == -1) && (errno == EAGAIN));

  return (pid);
}

void
at_the_end (void)
{				/* afficher un message de terminaison a la fin du processus */
  puts ("Goodbye !");
}


void erase (const char *path) 
{
	FILE	*f = fopen (path, "w");

	if(!f)
	{
		perror("fopen");
		abort();
	}

	fclose(f);
}

