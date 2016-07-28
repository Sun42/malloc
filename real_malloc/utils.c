/*
** utils.c for  in /u/all/sundas_c/cu/public/malloc/test_so
**
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
**
** Started on  Sun Mar  8 13:47:02 2009 christophe sundas
** Last update Sun Mar  8 22:12:14 2009 tugdual sarazin
*/
#include <string.h>
#include <stdlib.h>
#include "mymalloc.h"

void		*do_realloc(void *ptr, size_t taille, unsigned int nunites)
{
  t_header	*header_bloc;
  t_header	*header_newbloc;
  int		old_size;

  header_bloc = (t_header *)ptr - 1;
  old_size = (header_bloc->size - 1);
  if (nunites > header_bloc->size)
    {
      if ((header_newbloc = malloc(taille)) == NULL)
	return (NULL);
      memmove((void *)((t_header *)header_newbloc),
      (void *)((t_header *)header_bloc + 1), old_size * SIZE_BLOC);
      free((void *)((t_header *)header_bloc + 1));
      return ((void *)((t_header *)header_newbloc));
    }
  if (nunites == header_bloc->size)
    return (ptr);
  if (nunites < header_bloc->size)
    {
      header_newbloc = (t_header *)header_bloc + nunites;
      header_newbloc->size = header_bloc->size - nunites;
      free((void *)((t_header *)header_newbloc + 1));
      return (ptr);
    }
  return (NULL);
}

t_header	*do_malloc(size_t taille, t_header *pstart_free,
 t_header *pstart_alloc)
{
  t_header	*cur;
  unsigned int	nbblocks;

  nbblocks = get_real_size(taille);
  if ((cur = find_freeblock(nbblocks, pstart_free)) == NULL)
  {
    if (ask_memory(nbblocks) == 0)
      return (NULL);
  }
  else
  {
    cur->size = get_real_size(taille);
    add_list_alloc(pstart_alloc, cur);
    return ((t_header *)cur + 1);
  }
  if ((cur = find_freeblock(nbblocks, pstart_free)) == NULL)
    return (NULL);
  else
  {
    cur->size = get_real_size(taille);
    add_list_alloc(pstart_alloc, cur);
    return ((t_header *)cur + 1);
  }
}

void	init(t_header *start_free, t_header *start_alloc, int *start)
{
  start_free->next = start_free;
  start_free->size = 0;
  start_alloc->next = start_alloc;
  start_alloc->size = 0;
  *start = 1;
}

unsigned int	get_real_size(unsigned int octets)
{
  unsigned int	nb;

  nb = 1 + (octets / SIZE_BLOC);
  if (octets % SIZE_BLOC != 0)
    nb++;
  return (nb);
}
