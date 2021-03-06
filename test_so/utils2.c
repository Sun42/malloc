/*
** utils2.c for  in /u/all/sundas_c/cu/public/malloc/test_so
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar  8 13:47:07 2009 christophe sundas
** Last update Sun Mar  8 13:52:56 2009 christophe sundas
*/
#include <strings.h>
#include <stdlib.h>
#include <sys/types.h>
#include "my.h"
#include "mymalloc.h"

void		*calloc(size_t number, size_t size)
{
  void		*ptr;

  if ((ptr = malloc(number * size)) == NULL)
    return (NULL);
  bzero(ptr, number * size);
  return (ptr);
}

void	my_swaplist(t_header **prev, t_header **cur,
 t_header **next, int *flag)
{
  *flag = 1;
  (*prev)->next = (*next);
  (*next)->next = (*cur);
  (*cur)->next = (*next)->next;

}

void		real_show_allocmem(t_header *pstart_alloc)
{
  t_header	*prev;
  t_header	*cur;
  t_header	*next;
  int		flag;

  flag = 1;
  while (flag)
  {
    flag = 0;
    prev = pstart_alloc;
    cur = prev->next;
    next = cur->next;
    while (next != pstart_alloc)
    {
      if (cur != pstart_alloc)
      {
	if (cur > next)
	  my_swaplist(&prev, &cur, &next, &flag);
      }
      prev = cur;
      cur = next;
      next = next->next;
    }
  }
  my_aff_alloclist(pstart_alloc);
}
