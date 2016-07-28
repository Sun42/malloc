/*
** mymalloc.c for  in /u/all/sundas_c/cu/public/malloc/test_so
**
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
**
** Started on  Sun Mar  8 13:46:36 2009 christophe sundas
** Last update Sun Mar  8 22:45:52 2009 christophe sundas
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "mymalloc.h"

void	my_putstr_error(char *str)
{
  write(2, str, strlen(str));
}

void	my_putchar(char c)
{
  if (write(1, &c, 1) < 0)
    my_putstr_error("malloc: write error");
}

void	my_putstr(char *str)
{
  if (write(1, str, strlen(str)) < 0)
    my_putstr_error("malloc: write error");
}

void		my_put_hexa(unsigned int nb)
{
  int		i;
  unsigned char	num;
  unsigned int	filtr;

  i = 28;
  filtr = 0xF0000000;
  while (filtr)
  {
    num = (filtr & nb) >> i;
    if (num > 9)
      my_putchar(num + 55);
    else
      my_putchar(num + '0');
    filtr = filtr >> 4;
    i -= 4;
  }
}

void	my_put_nbr(unsigned int nb)
{
  char	num;
  int	i;
  int	flag;

  flag = 0;
  i = 100000000;
  while (i >=1)
    {
      num = (nb / i) % 10 + 0x30;
      if ((num != '0' || flag == 1) || (i == 1 && flag == 0))
	{
	  flag = 1;
	  my_putchar(num);
	}
      i = i / 10;
    }
}
