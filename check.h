#ifndef __CHECK_H
#define __CHECK_H

#include <stdbool.h>
#include <sys/types.h>

/* verifie si un chemin existe */

bool check_current_path_does_exist (size_t i_sc, size_t i_ac,
				    struct path ** matrix);

size_t srch_lowest_index (weight * w_p, size_t s);
#endif
