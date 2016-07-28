/*
** mymalloc.h for  in /u/all/sundas_c/cu/public/malloc/test_so
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Sun Mar  8 13:46:09 2009 christophe sundas
** Last update Sun Mar  8 13:46:10 2009 christophe sundas
*/
#ifndef __MYMALLOC_H__
# define __MYMALLOC_H__

#include <sys/types.h>
#define NALLOC 4096
#define FAVSIZE 4
#define SIZE_BLOC sizeof(t_header)
#define JUNK_LOW "junk pointer, too low to make sense \n"
#define JUNK_HIGH "junk pointer, too high to make sense\n"
#define ALREADY_FREE	"chunk is already free \n"
#define WRONG_FREE "warning modified (chunk-) pointer\n"
#define	MEM_ERROR	"out of memory.\n"

typedef	struct s_header
{
  struct s_header	*next;
  unsigned int		size;
} t_header;

/*
** malloc.c
*/
void		*malloc(size_t taille);
void		*realloc(void *ptr, size_t taille);
void		free(void *ptr);
int		ask_memory(unsigned int unite);
void		show_alloc_mem();

/*
** utils.h
*/
unsigned int	get_real_size(unsigned int octets);
void		init(t_header *start_free, t_header *start_alloc, int *start);
void		real_show_allocmem(t_header *pstart_alloc);
t_header	*do_malloc(size_t taille, t_header *pstart_free,
t_header *pstart_alloc);
void		*do_realloc(void *ptr, size_t taille, unsigned  int nunites);

/*
** utils2.h
*/
void		*calloc(size_t number, size_t size);
void		my_swaplist(t_header **prev, t_header **cur, t_header **next, int *flag);
void		real_show_allocmem(t_header *pstart_alloc);

/*
** list.c
*/
t_header	*find_freeblock(unsigned int nb, t_header *pstart_free);
void		insert_freelist(void *ptr, t_header *pstart_free);
void		fusion(t_header **prev, t_header **cur, t_header **to_insert);
void		add_list_alloc(t_header *start_alloc, t_header *new_alloc);
int		del_list_alloc(t_header *start_alloc, t_header *addr);

/*
** list.h
*/
void		my_aff_header(t_header *header);
void		my_aff_list(int opt, t_header *pstart_free, t_header *pstart_alloc);
void		showmem(char *addr, int size);
void		my_aff_freelist(t_header *pstart_free);
void		my_aff_alloclist(t_header *pstart_alloc);

#endif /* __MYMALLOC_H__*/
