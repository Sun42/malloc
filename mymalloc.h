#ifndef __MYMALLOC_H__
# define __MYMALLOC_H__

#define NALLOC 512
#define SIZE_BLOC       sizeof(t_header)

typedef	struct s_header
{
  struct s_header	*next;
  unsigned int		size;
} t_header;

void            *mymalloc(size_t taille);
void            *myrealloc(void *ptr, size_t taille);
void            myfree(void *ptr);


#endif /* __MYMALLOC_H__*/
