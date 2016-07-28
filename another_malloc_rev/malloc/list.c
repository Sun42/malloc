/*
** list.c for  in /u/all/sundas_c/cu/public/malloc/test_so
**
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
**
** Started on  Sun Mar  8 13:45:57 2009 christophe sundas
** Last update Sun Mar  8 22:02:08 2009 tugdual sarazin
*/
#include <stdlib.h>
/*#include "my.h"*/
#include "mymalloc.h"

t_header	*find_freeblock(unsigned int nb, t_header *pstart_free)
{
  t_header	*header;
  t_header	*prev;
  t_header	*new_header;

  prev = pstart_free;
  header = prev->next;
  while (header != pstart_free)
    {
      if (header->size == nb)
	{
	  prev->next = header->next;
	  return (header);
	}
      if (header->size > nb)
	{
	  header->size -= nb;
	  new_header = (t_header *)header + header->size;
	  new_header->size = nb;
	  return (new_header);
	}
      prev = header;
      header = header->next;
    }
  return (NULL);
}

void		insert_freelist(void *ptr, t_header *pstart_free)
{
  t_header	*to_insert;
  t_header	*cur;
  t_header	*prev;

  to_insert = (t_header *) ptr;
  prev = pstart_free;
  cur = prev->next;
  while (to_insert > cur && cur != pstart_free)
    {
      prev = cur;
      cur = cur->next;
    }
  to_insert->next = cur;
  prev->next = to_insert;
  fusion(&prev, &cur, &to_insert);
}

void	fusion(t_header **prev, t_header **cur, t_header **to_insert)
{
  if ((*to_insert) + (*to_insert)->size == (*to_insert)->next)
    {
      (*to_insert)->size += (*cur)->size;
      (*to_insert)->next = (*cur)->next;
    }
  if ((*prev) + (*prev)->size == (*prev)->next)
    {
      (*prev)->size += (*to_insert)->size;
      (*prev)->next = (*to_insert)->next;
    }
}

int		del_list_alloc(t_header *pstart_alloc, t_header *addr)
{
  t_header	*addr_list;
  t_header	*prev;

  if (pstart_alloc->next == NULL)
    pstart_alloc->next = pstart_alloc;
  prev = pstart_alloc;
  addr_list = pstart_alloc->next;
  while (addr_list != pstart_alloc)
    {
      if (addr_list == addr)
	{
	  prev->next = addr_list->next;
	  return (0);
	}
      prev = addr_list;
      addr_list = addr_list->next;
    }
  return (-1);
}

void	add_list_alloc(t_header *pstart_alloc, t_header *new_alloc)
{
  new_alloc->next = pstart_alloc->next;
  pstart_alloc->next = new_alloc;
}
