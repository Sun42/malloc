/*
** my_showmem.c for my_showmem in /u/epitech_2011s/sarazi_t/cu/rendu/piscine/Jour_06
**
** Made by tugdual sarazin
** Login   <sarazi_t@epitech.net>
**
** Started on  Tue Oct 14 15:59:10 2008 tugdual sarazin
** Last update Wed Mar  4 17:40:19 2009 tugdual sarazin
*/

void	aff_txt(char *c, int cmpt)
{
  int	i;

  i = 0;
  while (i < 16 && i <= cmpt)
    {
      if (c[i] >= ' ' && c[i] <= '~')
	my_putchar(c[i]);
      else
	my_putchar('.');
      i = i + 1;
    }
}

void	my_puthexa(char c)
{
  char	u;
  char	w;

  u = 4;
  while (u >= 0)
    {
      w = (c & (0x0F << u)) >> u;
      if (w <= 0x09)
	my_putchar(w + '0');
      else if (w >= 0x0A && w <= 0x0F)
	my_putchar(w + 0x57);
      u = u - 4;
    }
}

void	aff_hexa(char *c, int cmpt)
{
  int	i;

  i = 0;
  while (i <= 15)
    {
      if (i <= cmpt)
	my_puthexa(c[i]);
      else
	{
	  my_putchar(' ');
	  my_putchar(' ');
	}
      if (i % 2 == 1)
	my_putchar(' ');
      i = i + 1;
    }
  my_putchar(' ');
}

void	aff_adr(int adr)
{
  int	i;
  unsigned int	nb;

  i = 0;
  while (i < 8)
    {
      nb = (adr & (0xF0000000 >> (4 * i))) >> (4 * (7 - i));
      if (nb <= 9)
	my_putchar('0' + nb);
      else if (nb >= 0x0A && nb <= 0x0F)
	my_putchar(nb + 0x57);
      i = i + 1;
    }
  my_putchar(':');
  my_putchar(' ');
}

int	my_showmem(char *str, int size)
{
  int	i;

  i = 0;
  while (i <= size)
    {
      aff_adr(i);
      aff_hexa(str + i, size - i);
      aff_txt(str + i, size - i);
      my_putchar('\n');
      i = i + 16;
    }
  return (0);
}
