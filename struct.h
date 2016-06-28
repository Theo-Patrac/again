#ifndef __STRUCT_H
#define __STRUCT_H

/* fichier d'en-tete structure */

#include <stdio.h>		/* pour que le compilateur prend en compte le type size_t */
#include <stdbool.h>		/* meme chose pour le type booleen */

/* matrice de chemins */
struct path
{
  short next_city;		/* numero ville suivante */
  short distance;		/* distance pour aller a la ville suivante */
};

/* liaison */
struct route
{
  size_t index_of_starting_city;	/* index ville de depart */
  size_t index_of_arrival_city;	/* index ville d'arrivee */
  int distance;			/* distance entre les 2 noeuds */
};

/* structure pour tableau de poid */

typedef struct
{
  size_t node;			/* noeud */
  long weight;			/* poid du noeud */
  bool check;			/* pour verifier si le noeud a etait 
				   deja emprunte */
} weight;


/* 			---- !!!! ----
 lifo structure pour la pile des noeuds fils dans l algorithme de dijkstra,
 on push sur la pile quand un trouve un noeud fils partant de la ville courante 
*/

typedef struct element element;

struct element
{
  size_t val;
  struct element *nxt;
};

typedef element *llist;

#endif
