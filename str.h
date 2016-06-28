#ifndef __STR_H
#define __STR_H

void print (const char *str);	/* affichage non formate et sans '\n' */
bool check (const char *pattern, char **src, size_t size);	/* verifie si un char* est present dans un                                                          char** */
void search (char *s);		/* enleve les '\n' et purge stdin */
size_t c_count (const char *str, int c);	/* occurence d'un char dans un char* */

#endif /* str.h inclued */
