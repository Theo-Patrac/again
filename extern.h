#ifndef __EXTERN_H
#define __EXTERN_H

#include <sys/types.h>

void purge (void);		/* vide stdin */
pid_t create_process (void);	/* creation d un processus */
void at_the_end (void);		/* affiche un message de terminaison du processus */
void erase (const char *path) ;

#endif /* extern.h inclued */
