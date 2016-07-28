#ifndef __H_MYMALLOC__

# define __H_MYMALLOC__

#ifndef NULL
# define NULL (void *)0
#endif

/*#define DEBUG_MODE  */
#define NALLOC 1024




union header_block
{
  struct
  {
    union header_block	*next;
    union header_block	*prev;
    unsigned int size;
  } s;
  long x;
};

typedef union header_block header;


void		*mymalloc(unsigned noctets);
void            myfree(void * ptr);
void		my_putptr(char *str, header *p);
void		my_aff_freelist();
#endif
