/*
** show_list.c for  in /u/all/sundas_c/cu/public/malloc/test_so
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar  8 13:46:50 2009 christophe sundas
** Last update Sun Mar  8 13:46:51 2009 christophe sundas
*/
#include "my.h"
#include "mymalloc.h"

void    my_aff_list(int opt, t_header *pstart_free, t_header *pstart_alloc)
{
  if (opt == 1)
    my_aff_freelist(pstart_free);
  if (opt == 2)
    my_aff_alloclist(pstart_alloc);
  if (opt == 3)
    real_show_allocmem(pstart_alloc);
  if (opt == 4)
    {
      my_aff_freelist(pstart_free);
      my_aff_alloclist(pstart_alloc);
    }
}

void    my_aff_header(t_header *header)
{
  my_putstr("Addr : 0x");
  my_put_nbr((unsigned)header);
  my_putstr("\nNext : 0x");
  my_put_nbr((unsigned)header->next);
  my_putstr("\nSize : ");
  my_put_nbr(header->size);
  my_putstr(" unites (");
  my_put_nbr(header->size * SIZE_BLOC);
  my_putstr(" octets)\n");
  my_putstr("Calc : 0x");
  my_put_nbr((unsigned)header + header->size);
  my_putstr("\n\n\n");
}

void	my_aff_freelist(t_header *pstart_free)
{
  t_header      *header;

  header = pstart_free;
  my_aff_header(pstart_free);
  while (header->next != pstart_free)
    {
      header = header->next;
      my_aff_header(header);
    }
}

void    my_aff_alloclist(t_header *pstart_alloc)
{
  t_header      *header;

  header = pstart_alloc;
  my_aff_header(pstart_alloc);
  while (header->next != pstart_alloc)
    {
      header = header->next;
      my_aff_header(header);
    }
}
