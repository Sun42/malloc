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

static	t_header	start_free;
static	t_header	start_alloc;
static	void		*min_addr;
static			int start;
int	cpt = 0;
/*
** mini header
*/

void		*mymalloc(size_t taille);
void		*myrealloc(void *ptr, size_t taille);
void		myfree(void *ptr);

/*
void		*malloc(size_t taille);
void		*realloc(void *ptr, size_t taille);
void		free(void *ptr);
*/
unsigned int	get_real_size(unsigned int octets);
int		ask_memory(unsigned int unite);
void		my_aff_header(t_header *header);
void		my_aff_freelist();
t_header	*find_freeblock(unsigned int nb);
void		insert_freelist(void *ptr);
void		show_alloc_mem();
void		fusion(t_header	**prev, t_header **cur, t_header **to_insert);
void	add_list_alloc(t_header *start_alloc, t_header *new_alloc);
int		del_list_alloc(t_header *start_alloc, void *addr);
void    debug_showmem();
void    my_aff_alloclist();

void		*mymalloc(size_t taille)
{
  unsigned  int	nbblocks;
  t_header	*cur;
/*  my_putstr("############## MALLOC #########  taille");
  my_put_nbr(taille);
  my_putchar('\n');*/
  cpt++;
  nbblocks = get_real_size(taille);
  if (taille <= 0)
    return (NULL);
  if (!start)
    {
      start_free.next = &start_free;
      start_free.size = 0;
      start_alloc.next = &start_alloc;
      start_alloc.size = 0;
      start = 1;
      min_addr = sbrk(0);
    }
  if ((cur = find_freeblock(nbblocks)) == NULL)
    {
      if (ask_memory(nbblocks) == 0)
	return (NULL);
    }
  else
    {
      cur->size = get_real_size(taille);
      add_list_alloc(&start_alloc, cur);
      return ((t_header *)cur + 1);
    }
  if ((cur = find_freeblock(nbblocks)) == NULL)
    return (NULL);
  else
    {
      add_list_alloc(&start_alloc, cur);
      cur->size = get_real_size(taille);
      return ((t_header *)cur + 1);
    }
}

void	add_list_alloc(t_header *pstart_alloc, t_header *new_alloc)
{

  new_alloc->next = pstart_alloc->next;
  pstart_alloc->next = new_alloc;

}

int		del_list_alloc(t_header *pstart_alloc, void *addr)
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

t_header	*find_freeblock(unsigned int nb)
{
  t_header	*header;
  t_header	*prev;
  t_header	*new_header;

  prev = &start_free;
  header = prev->next;
  while (header != &start_free)
    {
      if (header->size == nb)  /*bloc parfait*/
        {
	  prev->next = header->next;
	  /*	  header->size = nb;*/
	  header->next = (t_header *)0x42;
	  return (header);
        }
      /* si block trop grand*/
      if (header->size > nb)
        {
	  header->size -= nb;
	  new_header = (t_header *)header + header->size;
	  new_header->size = nb;
	  /*	  new_header->next = new_heade  + nb;*/
	  new_header->next = (t_header *)0x42;
	  return (new_header);
        }
      prev = header;
      header = header->next;
    }
  return (NULL);
}


int	ask_memory(unsigned int unite)
{
  int		nb;
  void		*addr;
  t_header	*header;
  struct	rlimit	rlp;
  /*
  my_putstr("Ask memory ");
  my_put_nbr(unite);
 my_putstr("\n Sbrk(0) : ");
  my_put_nbr((unsigned )sbrk(0));
  getrlimit(RLIMIT_DATA,&rlp);
  my_putstr(" \nRlimit  cur:");
  my_put_nbr((unsigned )rlp.rlim_cur);
  my_putstr(" \n Rlimit  max:");
  my_put_nbr((unsigned int)rlp.rlim_max);
  my_putchar('\n');
  */
  if (unite <  NALLOC)
     unite = NALLOC;
  nb = (unite) * sizeof(t_header);
  /*
  my_put_nbr(nb);
  my_putchar('\n');
  */
  addr = sbrk(nb);
  if ((char *) addr == (char *) - 1)
    {
      /*
      my_putstr("Can't allocate memory \n");
      my_put_nbr_error(errno);
      */
      errno = 12;
      return (0);
    }
  header = (t_header *)addr;
  header->size = (nb / sizeof(t_header));
  header->next = NULL;
  insert_freelist((void *)addr);
  return (1);
}

void	fusion(t_header	**prev, t_header **cur, t_header **to_insert)
{
  /* fusion haut*/
  if ((*to_insert) + (*to_insert)->size == (*to_insert)->next)
    {
      /*
      my_putstr("Fusion haut \n");
      */
      (*to_insert)->size += (*cur)->size;
      (*to_insert)->next = (*cur)->next;
    }
  /* fusion bas*/
  if ((*prev) + (*prev)->size == (*prev)->next)
    {
      /*
      my_putstr("Fusion bas \n");
      */
      (*prev)->size += (*to_insert)->size;
      (*prev)->next = (*to_insert)->next;
    }
}


void	insert_freelist(void *ptr)
{
  t_header	*to_insert;
  t_header	*cur;
  t_header	*prev;

  to_insert = (t_header *) ptr;

  prev = &start_free;
  cur = prev->next;
  while (to_insert > cur && cur != &start_free)
    {
      prev = cur;
      cur = cur->next;
    }
  to_insert->next = cur;
  prev->next = to_insert;
  fusion(&prev, &cur, &to_insert);
}

void	myfree(void *ptr)
{

  /*
  my_putstr("############## FREE ######### \n");
  my_put_nbr(ptr);
  */
  /* todo some control*/
  if (ptr == NULL)
    return ;
  if (del_list_alloc(&start_alloc, (t_header *)ptr - 1) == -1)
    my_putstr("echoue");
  insert_freelist((t_header *)ptr - 1);
}


int	test_memory(t_header *header)
{
  if (header->next == (t_header *)0x42)
    return (1);
  return (-1);
}

void	*myrealloc(void *ptr, size_t taille)
{
 t_header        *header_bloc;
 t_header        *header_newbloc;
 int           old_size;
 unsigned int           nunites;

 /*
 my_putstr("############## REALLOC #########  taille :");
 my_put_nbr(taille);
 my_putstr("Pointeur a realloc :");
 my_put_nbr((unsigned int)ptr);
 my_putchar('\n');
 */
 if (ptr == NULL)
   return (mymalloc(taille));
 header_bloc = (t_header *)ptr - 1;
 if (header_bloc->next != (t_header *)0x42)
   return (NULL);
 /*my_aff_header(header_bloc);*/
if (taille == 0)
   {
     myfree(ptr);
     return (NULL);
   }
 /*
 my_putstr("Bloc a realloc :");
 my_aff_header(header_bloc);
 */
 nunites = get_real_size(taille);
 old_size = (header_bloc->size - 1);
 if (nunites > header_bloc->size)
   {
     if ((header_newbloc = mymalloc(taille)) == NULL)
       return (NULL);
     memcpy((void *)((t_header *)header_newbloc),(void *)((t_header *)header_bloc + 1), old_size * SIZE_BLOC);
     /*     header_newbloc->next = (t_header *)0x42;
     header_newbloc->size = nunites;*/
     myfree((void *)((t_header *)header_bloc + 1));
     return ((void *)((t_header *)header_newbloc));
   }
 if (nunites == header_bloc->size)
   return (ptr);
 if (nunites < header_bloc->size)
   {
      header_newbloc = (t_header *)header_bloc + nunites;
      header_newbloc->size = header_bloc->size - nunites;
      header_bloc->next = (t_header *)0x42;
      myfree((void *)((t_header *)header_newbloc + 1));
      return (ptr);
   }
 return (NULL);
}

void	my_aff_freelist()
{
  t_header	*header;

  my_putstr("\n------ Free list \n");
  header = &start_free;
  my_aff_header(&start_free);
  while (header->next != &start_free)
    {
      header = header->next;
      my_aff_header(header);
    }
}

void    my_aff_alloclist()
{
  t_header      *header;

  header = &start_alloc;
  my_aff_header(&start_alloc);
  while (header->next != &start_alloc)
    {
      header = header->next;
      my_aff_header(header);
    }
}
void    debug_showmem()
{
  my_putstr("------- Alloc list ---------------\n");
  my_aff_alloclist();
  my_putstr("-------- Free list ---------------\n");
  my_aff_freelist();
}


void		show_alloc_mem()
{

  t_header	*header_free;
  t_header	*header_alloc;
  void		*end_addr;

  end_addr = sbrk(0);
  my_putstr("\nstart addr\n");
  my_aff_header(&start_free);
  header_free = start_free.next;
  printf("\n\nheader_free %p\n", (void *)header_free);
  while (header_free != &start_free)
    {
      if (header_free->next == header_free + header_free->size)
	printf("CONTIGUE\n");
      else
	printf("PAS CONTIGUE\n");
      my_aff_header(header_free);
      header_alloc = header_free + header_free->size;
      while (header_alloc != header_free->next && (void *)header_alloc < end_addr)
	{
	  printf("FIND BLOC ALLOC\n");
	  if (test_memory(header_alloc) < 0)
	    printf("Error memory\n");
	  else
	    printf("memory OK\n");
	  my_aff_header(header_alloc);
	  header_alloc += header_alloc->size;
	}
      header_free = header_free->next;
    }
}

unsigned int	get_real_size(unsigned int octets)
{
  unsigned int	nb;

  nb = 1 + (octets / SIZE_BLOC);
  if (octets % SIZE_BLOC != 0)
    nb++;
  return (nb);
}

void	showmem(char *addr, int size)
{
  int	i;

  i = 0;
  while (i < size)
  {
    if (addr[i] >= ' ' && addr[i] <= '~')
      my_putchar(addr[i]);
    else
      my_putchar('.');
    i++;
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

  /*
  showmem((char *)((unsigned)header + sizeof(t_header)), header->size * sizeof(t_header));
  */
}
