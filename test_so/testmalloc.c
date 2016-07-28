#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my.h"
#include "malloc.h"
#include <sys/types.h>
#ifndef HAVE_NOT_UNISTD_H
# include <unistd.h>
#endif

int		main()
{
  char		*addr;
  char		*addr2;
  char		*addr3;
  char		*addr4;
  
  addr = mymalloc(45);
  

  addr2 = mymalloc(17);
 
   
  addr3 = mymalloc(9);
  

  addr4 = mymalloc(1);
 
 
 
    myfree(addr4);
   myfree(addr3);   
   myfree(addr2); 
    myfree(addr);
/*printf(" Free list : \n");
   */
   my_aff_freelist();
  /*  printf(" Alloc list : \n");
  show_alloc_mem();
  */
 return (0);
}
