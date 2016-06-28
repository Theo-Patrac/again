#ifndef __LIFO_H
#define __LIFO_H

llist push_at_the_end (llist liste, int data);
llist push_at_the_head (llist liste, int data);
llist pop_at_the_head (llist liste);
llist pop_at_the_end (llist liste);
llist search_element (llist liste, size_t data);
llist delete_lifo (llist liste);
void display_lifo (llist liste, char **cities);
int lifo_is_empty (llist liste);

#endif
