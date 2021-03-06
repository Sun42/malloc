#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "my.h"
#include "malloc.h"

void	my_aff_header(header *header_bloc);
header	*get_fitbloc(unsigned int nunites);
header	*get_newbloc(unsigned int nunites);
void	*realloc(void *ptr, int taille);



static header   base;
static header   *plibre = NULL;
static header	basealloc;
static header	*plibrealloc;

static header	*ask_memory(unsigned int nu)
{
  char		*addr;
  header	*pu;
    
  if (nu < NALLOC)
    nu = NALLOC;
  my_putstr("ASk memory de");
  my_put_nbr(nu);
  my_putchar('\n');
  addr = (char *)sbrk(nu * sizeof(header));
  if (addr == (char *) - 1)
    {
      my_put_nbr_error(errno);
      return NULL;
    }
  pu = (header *) addr;
  pu->s.size = nu;
  myfree((void *) (pu + 1)); /* on introduit le nouvel espace memoire dans la liste*/
  return plibre;
}

/*
** met le bloc pu dans la liste des blocs libres;
*/
void		myfree(void * ptr)
{
  header	*pt;
  header	*freelist;
  
  pt = (header *) ptr - 1; /*pt pointe vers le header du block a free */
  freelist = plibre;
  while (freelist > pt || freelist->s.next < pt)
    {
      if (freelist >= freelist->s.next && (pt > freelist || pt < freelist->s.next))  /* bloc libere en debut ou fin*/
	break;
      freelist = freelist->s.next;
    }
  if (pt + pt->s.size == freelist->s.next)  /* fusion , on agrandi le bloc pt*/
    {
      pt->s.size += freelist->s.next->s.size;
      pt->s.next = freelist->s.next->s.next;
    }
  else
    pt->s.next = freelist->s.next;
  if (freelist + freelist->s.size == pt)  /* fusion par le bas */
    {
      freelist->s.size += pt->s.size;
      freelist->s.next = pt->s.next;
    }
  else
    freelist->s.next = pt;
  plibre = freelist;
}

void	*mymalloc(unsigned int noctets)
{
  header		*p;
  header		*pprec;
  unsigned	int	nunites;
  
  nunites = (noctets + sizeof(header)- 1) / sizeof(header) + 1; /* + 1 pour le block header*/
  if ((pprec = plibre) == NULL)/* PREMIER APPEL plibre pointe sur lui mem*/
      {
	pprec = plibre = base.s.next = &base;
	base.s.size = 0;
      }
  p = pprec->s.next;
  while (1)
    {
      if (p == plibre)
        {
          if ((p = ask_memory(nunites)) == NULL)/* si on arrive au dernier alors il n'y a pas de blocs suffisement grand , on ask memory*/
            return NULL;
        }
      if (p->s.size >= nunites)/* si bloc suffisamment grand*/
	{
	  if (p->s.size == nunites)
	    pprec->s.next = p->s.next;/* on retire le block p de la liste en  faisant pointer le precedent vers le next */
	  else /*on reduit le bloc trop grand, ki va rester */
	    {
	      p->s.size -= nunites;
	      p += p->s.size;
	      p->s.size = nunites;
	      
	    }
	  plibre = pprec;
	  return (void *) (p + 1);
	}
      pprec = p;
      p = p->s.next;
    }
}

void	*realloc(void *ptr, int taille)
{
  header	*header_bloc;
  header	*header_newbloc;
  int		old_size;
  int		nunites;


  header_bloc = (header *)ptr - 1;
  my_putstr("Bloc a realloc :");
  my_aff_header(header_bloc);
  nunites = ((taille + sizeof(header)- 1) / sizeof(header) + 1) + header_bloc->s.size;
  if ((header_newbloc = get_newbloc(nunites)) == NULL)
    return (NULL);
  old_size = header_bloc->s.size * sizeof(header_bloc);
  memmove((void *)((header *)header_newbloc + 1),(void *)((header *)header_bloc + 1), old_size);
  myfree((void *)((header *)header_bloc + 1));
  return ((void *)((header *)header_newbloc + 1));
}

header	*get_newbloc(unsigned int nunites)
{
  header	*header_bloc;

  if (nunites <= 0)
    return (NULL);
  if ((header_bloc = get_fitbloc(nunites)) != NULL)
    {
      my_putstr("Bloc assez grand existe \n");
      return (header_bloc);
    }
  else
    {
      my_putstr("Bloc assez grand existe pas \n");
      ask_memory(nunites);
      return (get_fitbloc(nunites));
    }
}

header	*get_fitbloc(unsigned int nunites)
{
  header        *cur;
  header	*prev;
  
  prev = &base;
  cur = prev->s.next;
  while (cur != &base)
    {
      if (cur->s.size >= nunites)
	{
	  if (cur->s.size == nunites)
	    prev->s.next = cur->s.next;
	  else
	    {
	      cur->s.size -= nunites;  
	      cur += cur->s.size;
	      cur->s.size = nunites;
	    }
	  plibre = prev;
	  return (cur);  
	}
      prev = cur;
      cur = cur->s.next;
    }
  return (NULL);
}

void	my_aff_freelist()
{
  header	*cur;
  int		i;
  header	*prev;
  
  printf("\nAdresse de base %p \n", (char *)&base);
  /*printf("\nAdresse de plibre %p \n", (char *)plibre);*/
  my_putstr("Affichage de la freelist : \n");
  i = 1;
  prev = &base;
  cur = prev->s.next;
  /*
  my_putstr("Plibre ");
  my_aff_header(plibre);
  */
my_aff_header(prev);
  while (cur != &base)
    {
      my_putstr("Bloc numero ");
      my_put_nbr(i);
      my_putchar(' ');
      my_aff_header(cur);
      prev = cur;
      cur = cur->s.next;
      i++;
    }
}


void	my_aff_header(header *header_bloc)
{
  my_putstr("\n----------------------------------------\n");
  my_putstr("Header de bloc ");
  printf("%p \n",(char *) header_bloc);
  my_showmem((char *)header_bloc, sizeof(header));
  my_putstr("De la taille de  ");
  my_put_nbr(header_bloc->s.size);
  my_putstr("\nPointe vers ");
  my_showmem((char *)header_bloc->s.next, sizeof(header*));
  printf("%p \n",(char *) header_bloc->s.next);
  my_putstr("\n----------------------------------------\n");
}
