#include <stdlib.h>

int	main()
{
  void	*addr;

  addr = malloc(10);
  realloc(addr, 30);
}
