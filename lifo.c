#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "macro.h"
#include "struct.h"
#include "lifo.h"

llist
push_at_the_end (llist liste, int data)
{
  /* On crée un nouvel élément */
  element *nouvelElement = malloc (sizeof (element));

  /* On assigne la valeur au nouvel élément */
  nouvelElement->val = data;

  /* On ajoute en fin, donc aucun élément ne va suivre */
  nouvelElement->nxt = NULL;

  if (liste == NULL)
    {
      /* Si la liste est videé il suffit de renvoyer l'élément créé */
      return nouvelElement;
    }

  else
    {
      /* Sinon, on parcourt la liste à l'aide d'un pointeur temporaire et on
         indique que le dernier élément de la liste est relié au nouvel élément */

      element *temp = liste;

      while (temp->nxt != NULL)
	{
	  temp = temp->nxt;
	}

      temp->nxt = nouvelElement;

      return liste;
    }
}

llist
push_at_the_head (llist liste, int data)
{
  /* On crée un nouvel élément */
  element *nouvelElement = malloc (sizeof (element));

  /* On assigne la valeur au nouvel élément */
  nouvelElement->val = data;

  /* On assigne l'adresse de l'élément suivant au nouvel élément */
  nouvelElement->nxt = liste;

  /* On retourne la nouvelle liste, i.e. le pointeur sur le premier élément */
  return nouvelElement;
}

llist
pop_at_the_head (llist liste)
{
  if (liste != NULL)
    {
      /* Si la liste est non vide, on se prépare à renvoyer l'adresse de

         l'élément en 2ème position */
      element *aRenvoyer = liste->nxt;

      /* On libère le premier élément */
      free (liste);

      /* On retourne le nouveau début de la liste */
      return aRenvoyer;
    }
  else
    {
      return NULL;
    }

}

llist
pop_at_the_end (llist liste)
{
  /* Si la liste est vide, on retourne NULL */
  if (liste == NULL)
    return NULL;

  /* Si la liste contient un seul élément */

  if (liste->nxt == NULL)
    {
      /* On le libère et on retourne NULL (la liste est maintenant vide) */
      free (liste);

      return NULL;
    }

  /* Si la liste contient au moins deux éléments */
  element *tmp = liste;
  element *ptmp = liste;

  /* Tant qu'on n'est pas au dernier élément */
  while (tmp->nxt != NULL)
    {
      /* ptmp stock l'adresse de tmp */
      ptmp = tmp;
      /* On déplace tmp (mais ptmp garde l'ancienne valeur de tmp */
      tmp = tmp->nxt;
    }
  /* A la sortie de la boucle, tmp pointe sur le dernier élément, et ptmp sur
     l'avant-dernier. On indique que l'avant-dernier devient la fin de la liste
     et on supprime le dernier élément */
  ptmp->nxt = NULL;

  free (tmp);

  return liste;
}

llist
search_element (llist liste, size_t data)
{
  element *tmp = liste;

  /* Tant que l'on n'est pas au bout de la liste */
  while (tmp != NULL)
    {
      if (tmp->val == data)
	{

	  /* Si l'élément a la valeur recherchée, on renvoie son adresse */
	  return tmp;
	}
      tmp = tmp->nxt;
    }

  return NULL;
}

llist
delete_lifo (llist liste)
{

  element *tmp = liste;
  element *tmpnxt;

  /* Tant que l'on n'est pas au bout de la liste */
  while (tmp != NULL)
    {
      /* On stocke l'élément suivant pour pouvoir ensuite avancer */
      tmpnxt = tmp->nxt;

      /* On efface l'élément courant */
      free (tmp);

      /* On avance d'une case */
      tmp = tmpnxt;
    }

  /* La liste est vide : on retourne NULL */
  return NULL;
}

void
display_lifo (llist liste, char **cities)
{
  element *tmp = liste;
  size_t counter;

  counter = 1;

  /* Tant que l'on n'est pas au bout de la liste */
  while (tmp != NULL)
    {
      /* On affiche */
      printf ("%15s est un noeud fils, index: %03" PRIsz ".\n",
	      cities[tmp->val], tmp->val);
      /* On avance d'une case */
      tmp = tmp->nxt;
      ++counter;
    }
}

int
lifo_is_empty (llist liste)
{
  return (liste == NULL) ? 1 : 0;
}
