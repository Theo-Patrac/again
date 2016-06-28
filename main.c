#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <mcheck.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include "struct.h"
#include "input.h"
#include "str.h"
#include "memory.h"
#include "output.h"
#include "macro.h"
#include "extern.h"
#include "set.h"
#include "check.h"
#include "lifo.h"

int
main (void)
{
  short n;			/* nombre de villes */
  char **cities = NULL;		/* contient les noms des villes */
  char cmd[MAX_LENGTH_CMD];	/* buffer qui recoie les commandes 
				   et qui est interprete par la boucle principale */
  struct path **matrix = NULL;	/* matrice de chemins */
  struct route itinerary;	/* contient des informations sur un itineraire
				   1)       ->      index de la ville de depart
				   2)       ->      index de la ville d'arrivee
				   3)       ->      distance entre les deux villes
				 */
  bool check_input_city = false;	/* verifie si la saisie des villes
					   a deja etait effectuee */
  bool check_set_matrix_of_path = false;

  atexit (at_the_end);		/* message de terminaison */

  /* ----- options ----- */

  const char *opt1 = "ville";	//saisie de villes
  const char *opt2 = "exit";	//quitter
  const char *opt3 = "afficher";	//afficher les villes et les numeros des noeuds
  const char *opt4 = "clear";	//effacer la console
  const char *opt5 = "distance";	//implementation itineraire
  const char *opt6 = "chemin";	//affichage des chemins
  const char *opt7 = "parcours";	//parcours d un itineraire
  const char *opt8 = "optimise";	//parcours avec dijkstra

  /* ----- boucle principal ----- */

  while (true)
    {
      display_input_prompt ();

      fgets (cmd, MAX_LENGTH_CMD - 1, stdin);	/* lecture d'une option */
      search (cmd);		/* on enleve '\n' de cmd ou on purge stdin */

      /* ----- option 1: saisie de ville ----- */

      /* ----- cas 1: erreur, car saisie des villes deja effectuee ----- */

      if (((strlen (cmd) - c_count (cmd, SPACE) == strlen (opt1))
	   && (strstr (cmd, opt1) != NULL)) && (check_input_city == (true)))
	{
	  fprintf (stderr, "Saisie des villes deja effectuee\n");
	}

      /* cas 2: saisie des villes non effectuee */

      else if ((strlen (cmd) - c_count (cmd, SPACE) == strlen (opt1))
	       && (strstr (cmd, opt1) != NULL)
	       && (check_input_city == (false)))
	{
	  user_input_n_of_cities (&n);

	  /* allocation dynamique des villes */

	  if (alloc_cities (&cities, (size_t) n) == false)
	    return (EXIT_FAILURE);

	  /* saisie des villes */

	  user_input_cities (&cities, (size_t) n);

	  /* on regle la casse: 1 char <= touppercase le reste en tolowercase */

	  for (size_t i = 0; i < n; i++)
	    {
	      city_case (cities[i]);
	    }

	  /* On initialise la matrice des chemins. */

	  matrix = alloc_matrix_of_path ((size_t) n, N_OF_PATH_MAX);
	  set_next_city (&matrix, -1, (size_t) n, N_OF_PATH_MAX);
	  set_distance (&matrix, 0, (size_t) n, (size_t) N_OF_PATH_MAX);

	  /* On met un booleen a 'true' qui verifie si
	     la matrice des chemins a bien etait initialisee. */

	  check_set_matrix_of_path = true;

	  /* Le boolen suivant permettra de verifier si la saisie des villes
	     est verouillee ou non. */

	  check_input_city = true;
	}

      /* ----- option 2: quitter le processus ----- */

      else if ((strlen (cmd) - c_count (cmd, SPACE) == strlen (opt2))
	       && (strstr (cmd, opt2) != NULL))
	{
	  goto free_heap;
	}

      /* ----- option 3: afficher les noeuds et leurs numeros ----- */

      else if ((strcmp ("afficher", cmd) == 0) ^
	       (strcmp (cmd, "afficher;") == 0))
	{
	  display_all_cities (cities, (size_t) n);

	  /* ----- option 4: effacer l output de la console ----- */

	}
      else if ((strcmp ("clear", cmd) == 0)	/* effacer l'output de la console */
	       ^ (strcmp ("clear;", cmd) == 0))
	{
	  clrscr ();
	}

      /* ----- option 5: implementer une liaison ----- */

      /* ----- cas 1: erreur, car saisie des villes non-effectuee  ----- */

      else if (((strcmp (cmd, "distance") ==
		 0) ^ (strcmp (cmd, "distance;") == 0))
	       && (check_input_city == false))
	{
	  fprintf (stderr, "Veuillez saisir les villes, "
		   "avant d'implementer un intineraire\n");

	  /* ----- cas 2: saisie des villes deja effectuee  ----- */

	}
      else
	if (((strcmp (cmd, "distance") ==
	      0) ^ (strcmp (cmd, "distance;") == 0))
	    && (check_input_city == true))
	{
	  size_t index_sc;	/* index ville de depart */
	  size_t index_ac;	/* index ville arrivee */
	  size_t index_to_set_sc;
	  size_t index_to_set_ac;
	  bool current_path_does_exist;
	  bool sc_can_be_set;	/* verifie si un emplacement 
				   est libre pour la ville de depart */
	  bool ac_can_be_set;	/* verifie si un emplacement
				   est libre pour la ville d'arrivee */
	  int d;		/* distance */

	  current_path_does_exist = false;
	  itinerary = distance (cities, (size_t) n);
	  index_sc = itinerary.index_of_starting_city;
	  index_ac = itinerary.index_of_arrival_city;

	  /* l'instruction suivante verifie si le chemin est deja 
	     present dans la matrice de chemins */

	  if ((current_path_does_exist =
	       check_current_path_does_exist
	       (itinerary.index_of_starting_city,
		itinerary.index_of_arrival_city, matrix)) == true)
	    {
	      current_path_does_exist = true;	/* on verifie cela,
						   avec le boolen */
	    }

	  d = itinerary.distance;

	  sc_can_be_set = false;

	  /*              ----- ville de depart ----- 

	     on verifie si il y a une place 
	     de libre dans m[ville de depart][i].ville_suivante.
	   */

	  for (size_t i = 0; i < N_OF_PATH_MAX; i++)
	    {
	      if (matrix[index_sc][i].next_city != -1)
		sc_can_be_set = false;	/* ville_de_depart.ville_suivante 
					   ne peut pas recevoir le numero 
					   de la ville d arrivee */
	      else
		{
		  sc_can_be_set = true;	/* ville suivante vaut -1, 
					   on peut donc y deposer la
					   ville d arrivee */
		  index_to_set_sc = i;

		  break;
		}
	    }

	  if (sc_can_be_set == false)
	    {
	      fprintf (stderr, "Nombre de chemin max atteint vd\n");	/* erreur 5 chemins 
									   atteint partant de
									   la ville  de depart */
	    }

	  /*              ----- ville d arrivee ----- 
	     meme traitement pour la ville d arrivee 
	   */
	  for (size_t i = 0; i < N_OF_PATH_MAX; i++)
	    {
	      if (matrix[index_ac][i].next_city != -1)
		{
		  ac_can_be_set = false;
		}
	      else
		{
		  ac_can_be_set = true;
		  index_to_set_ac = i;

		  break;
		}
	    }

	  /* ----- cas 1: itineraire ne peut pas etre implemente ----- */

	  if ((ac_can_be_set == false) ^ (current_path_does_exist == true))
	    {
	      if (ac_can_be_set == false)
		fprintf (stderr, "Nombre de chemin max atteint.\n");
	      else
		fputs ("Chemin existant relie les deux villes.", stderr);

	      sc_can_be_set = false;
	      ac_can_be_set = false;
	    }

	  /* ----- cas 2: itineraire peut etre implemente ----- */

	  if ((sc_can_be_set == true) && (ac_can_be_set == true))
	    {
	      matrix[index_sc][index_to_set_sc].next_city = index_ac;
	      matrix[index_sc][index_to_set_sc].distance = d;

	      matrix[index_ac][index_to_set_ac].next_city = index_sc;
	      matrix[index_ac][index_to_set_ac].distance = d;
	    }
	}
      /* ----- option 6: affichage des chemins ----- */

      /* cas 1: erreur, saisie des villes non-effectuee, par consequent
         aucun chemin */

      else if ((strcmp (cmd, "chemin") == 0) ^
	       (strcmp (cmd, "chemin;") == 0) && (check_input_city == false))
	{
	  fputs ("Erreur, saisie de ville non-effectuee.", stderr);
	}

      /* cas 2: saisie des villes effectuee, affichage des villes et des chemins
         partant de chaque ville sous forme de tableau 

         -----------------------------------

         col 1: ville courante.ville_suivante
         col 2: distance liaison ville_courante-ville_courante.ville_suivante */

      else if ((strcmp (cmd, "chemin") == 0) ^ (strcmp (cmd, "chemin;") == 0))
	{
	  display_separation_of_row ();
	  puts ("|       [ville suivante]   "
		"|         [distance]        |");
	  display_separation_of_row ();

	  for (size_t i = 0; i < (size_t) n; i++)
	    {
	      for (size_t j = 0; j < 5; j++)
		{
		  printf ("|matrix[%" PRIsz "][%" PRIsz "]"
			  ".next_city=%03d|"
			  "matrix[%" PRIsz "][%" PRIsz "]"
			  ".distance=%05d|\n", i, j,
			  matrix[i][j].next_city, i, j,
			  matrix[i][j].distance);

		  if (j == 4)
		    {
		      display_separation_of_row ();
		    }

		}
	    }
	}

      /* ----- option 7: parcours trivial d une liaison (directe) ----- */

      /* ----- cas 1: erreur saisie des villes non effectuee ------ */

      else if ((strcmp (cmd, "parcours") == 0) ^
	       (strcmp (cmd, "parcours;") == 0)
	       && (check_input_city == false))
	{
	  fputs ("Erreur, saisie de(s) ville(s) non-effectuee", stderr);
	}
      /* ----- cas 2: saisie des villes effectuee ------ */

      else if ((strcmp (cmd, "parcours") == 0) ^
	       (strcmp (cmd, "parcours;") == 0))
	{
	  get_route (cities, (size_t) n, matrix);
	}

      /* ----- option 8: parcrous non trivial, recherche liaison optimal ----- */

      /* ----- cas 1: erreur, aucun(s) chemin(s) ------ */

      else if (((strcmp (cmd, "optimise") ==
		 0) ^ (strcmp (cmd, "optimise;") == 0))
	       && (check_set_matrix_of_path == false))
	{
	  fputs ("Erreur, aucun chemin existant.", stderr);
	}

      /* ----- cas 2: chemin(s) disponible(s) ------ */

      else if (((strcmp (cmd, "optimise") ==
		 0) ^ (strcmp (cmd, "optimise;") == 0))
	       && (check_set_matrix_of_path == true))
	{

	  /* ----- Dijkstra ----- */

	  FILE		*f = NULL;
	  char		*line = NULL;
	  bool 		dijkstra_continue;
	  bool 		first_loop;
	  char 		*sc = NULL;	//ville de depart
	  char 		*ac = NULL;	//ville arrivee
	  long 		w_cs;
	  long		w_f;
	  size_t 	index_sc;	//index ville de depart
	  size_t 	index_ac;	//index ville d'arrivee
	  size_t 	cc;		//index ville courante
	  size_t 	ics;		//index du fils courant
	  size_t 	s_array[N_OF_PATH_MAX - 1];	//tableau des noeuds fils
	  size_t 	n_of_son;
	  size_t	n_of_index;
	  size_t	iterator;
	  int		*index_array = NULL;
	  int 		*predecessor = malloc (sizeof (int) * n);
	  int		res;
	  int		start;
	  int		arrive;
	  weight 	*w_p = NULL;	//tableau des poids
	  llist 	s_lifo = NULL;
	  llist		s_index_lifo = NULL;
	  llist		s_temp;

	  alloc_and_memset_wp (&w_p, n);	//allocation de la structure des poids
	  alloc_c (&sc);	//allocation ville dep
	  alloc_c (&ac);	//allocation ville arrivee
	  if (predecessor == NULL)
	    {
	      perror ("malloc");
	      return (EXIT_FAILURE);
	    }

	  memset (predecessor, (-1), (sizeof (int) * (size_t) n));
	  sc = input_starting_city (sc, cities, (size_t) n);
	  ac = input_arrival_city (ac, cities, sc, (size_t) n);
	  index_sc = index_in_src (cities, sc, (size_t) n);
	  index_ac = index_in_src (cities, ac, (size_t) n);

	  w_p[index_sc].weight = 0;
	  dijkstra_continue = true;
	  first_loop = true;

	  size_t cpt = 1;

	  while (dijkstra_continue)
	    {   
		    cc = srch_lowest_index(w_p , n);
		    printf("\nville courante: %s.\n", cities[cc]);

		    for(size_t i = 0; i < N_OF_PATH_MAX; i++)
		    {
		          if(matrix[cc][i].next_city != -1 && matrix[cc][i].next_city != index_sc)
			  {
				  start = 0;
				  arrive = 0;
				  iterator = 0;
				  n_of_index = 0;
				  w_cs = 0;
				  ics = matrix[cc][i].next_city;
				  s_lifo = push_at_the_head(s_lifo, ics);
				  predecessor[ics] = cc;

				  res = ics;
				  
				  s_index_lifo = push_at_the_head (s_index_lifo, res);
				  n_of_index++;
				  
				  while(1)
				  {
					  res = predecessor[res];

					  if(res == -1) /* il n'y a plus de predecesseur on quitte la boucle */
						break;
				  	
					  s_index_lifo = push_at_the_head (s_index_lifo, res);
				  	  n_of_index++; /* chaque predecesseur de trouvé c'est un index de plus 
							   push sur la pile */
				  }

				  index_array = malloc(sizeof(int) * n_of_index); /* on alloue le tableau des indexs */
				  
				  erase ("result_sets.txt"); /* on efface les jeux de resultats antérieur */

				  s_temp = s_index_lifo;

				  for(s_temp; s_temp; s_temp = s_temp->nxt) /* on rempli de tableau
									       qui contient les indexs 
									       pour aller de la ville de depart 
									       au fils courant */
				  {
					  index_array[iterator] = s_temp->val;
					  iterator++;
				  }

				  if((f = fopen("result_sets.txt", "a")) == NULL)
				  {
					  perror("fopen");
					  abort();
				  }
				  
				  /* écriture du jeu de résultat */

				  for(size_t i = 0; i < n_of_index; i++)
				  {
					  if(n_of_index - 1 > i)
					  {
						  fprintf(f, "%d %d\n", index_array[i], index_array[i + 1]);
					  }
				  }

				  fclose (f);

				  f = fopen ("result_sets.txt", "r");

				  line = malloc(sizeof(char) * MAX_LENGTH_LINE);

				  while(fgets(line, MAX_LENGTH_LINE - 1, f) != NULL)
				  {
					  if(sscanf(line, "%d %d", &start, &arrive) != 2)
					  {
						  perror ("sscanf");
						  abort ();
					  }

					  w_cs += get_distance (start, arrive, matrix);
				  }


				  w_f = w_cs - get_distance (cc, ics, matrix);
				  /* on a le poid du fils :) */

				  printf("poid du fils courant:%ld poid du pere:%ld\n", w_cs, w_f);


	  			  free (line);
				  fclose (f);
				  free (index_array);
				  s_index_lifo = delete_lifo (s_index_lifo);
			  }
	            }

		    s_lifo = delete_lifo (s_lifo);

		    break;
	    }

	  free (predecessor);
	  free (w_p);		//on libere la structure de poid
	  free (sc);		//on libere la ville de depart
	  free (ac);		//on libere la ville d arrivee
	}

      else
	{
	  fprintf (stderr, "Choix inconnue\n");
	}

      printf ("\n");
    }

free_heap:			/* ----- on libere ce qui a etait alloue sur le tas ----- */
  if (check_input_city == true)
    {
      free_matrix_of_path (&matrix, (size_t) n);
      free_cities (&cities, (size_t) n);
    }

  return (EXIT_SUCCESS);
}
