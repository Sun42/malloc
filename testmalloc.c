#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my.h"
#include "mymalloc.h"
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


  addr = mymalloc(10);
 
addr2 = mymalloc(25);


  myfree(addr2);
  /*  
 myfree(addr);
*/
 debug_showmem();
/*
   debug_showmem();*/
/*  addr = mymalloc(15);
  addr = mymalloc(8);*/


  /*  my_aff_freelist();*/
/*printf(" Free list : \n");
   */

  /*  printf(" Alloc list : \n");
  show_alloc_mem();
  */

 return (0);
}
