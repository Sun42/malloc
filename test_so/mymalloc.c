/*
** mymalloc.c for  in /u/all/sundas_c/cu/public/malloc/test_so
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar  8 13:46:36 2009 christophe sundas
** Last update Sun Mar  8 13:51:33 2009 christophe sundas
*/
#include <sys/resource.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include "my.h"
#include "mymalloc.h"

static t_header	start_free;
static t_header	start_alloc;
static int	start;

void	*malloc(size_t taille)
{
  if (taille <= 0)
    return (NULL);
  if (!start)
    init(&start_free, &start_alloc, &start);
  return (do_malloc(taille, &start_free, &start_alloc));
}

int		ask_memory(unsigned int unite)
{
  int		nb;
  void		*addr;
  t_header	*header;

  if (unite < NALLOC)
     unite = NALLOC;
  nb = (unite) * sizeof(t_header);
  addr = sbrk(nb);
  if ((char *) addr == (char *) - 1)
    {
      my_putstr(MEM_ERROR);
      errno = 12;
      return (0);
    }
  header = (t_header *)addr;
  header->size = (nb / sizeof(t_header));
  header->next = NULL;
  insert_freelist((void *)addr, &start_free);
  return (1);
}

void	free(void *ptr)
{
  if (ptr == NULL)
    return ;
  if (del_list_alloc(&start_alloc, (t_header *)ptr - 1) == -1)
    {
      my_putstr_error(WRONG_FREE);
      return ;
    }
  insert_freelist((t_header *)ptr - 1, &start_free);
}

void		*realloc(void *ptr, size_t taille)
{
  unsigned int	nunites;

  if (ptr == NULL)
    return (malloc(taille));
  if (taille == 0)
  {
    free(ptr);
    return (NULL);
  }
  nunites = get_real_size(taille);
  return (do_realloc(ptr, taille, nunites));
}

void	show_alloc_mem()
{
  my_aff_list(3, &start_free, &start_alloc);
}
