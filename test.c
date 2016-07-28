#include <stdlib.h>
#include <errno.h>


void	my_puts(char *str)
{
  write(1, str, strlen(str));

}

void	myerror()
{
  my_puts("error STOP");
  if (errno == 12)
    my_puts("errno = 12");
  exit(-1);
}

int	main()
{
  unsigned	nb;
  char		*addr;

  addr = malloc(60);
  malloc(1);
  malloc(1);
  free(addr);

/*    nb = 1000000;
while (1)
  {
    printf("%d\n",nb);
    if (malloc(nb) == NULL)
      myerror();
      }*/

}
