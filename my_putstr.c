/*
** my_putstr.c for my_put_str.c in /u/all/sundas_c/cu/rendu/piscine/Jour_04
** 
** Made by christophe sundas
** Login   <sundas_c@epitech.net>
** 
** Started on  Thu Oct  9 15:09:57 2008 christophe sundas
** Last update Sat Feb 28 18:23:50 2009 christophe sundas
*/

int	my_putstr(char *str);
void	my_putchar(char c);

int	my_putstr(char *str)
{
  while (*str)
    {
      my_putchar(*str);
      str = str + 1;
    }
  return (0);
}

void	my_putchar(char c)
{
  write(1, &c, 1);
}
