/*
** echo.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri May  5 06:44:42 2017 Nicolas Polomack
** Last update Tue Oct 17 10:51:25 2017 nicolaspolomack
*/

#include <string.h>
#include <stdio.h>
#include "my.h"

char	get_escaped_char(char c)
{
  if (c == 'a')
    return (0x7);
  else if (c == 'b')
    return (0x8);
  else if (c == 'f')
    return (0xc);
  else if (c == 'n')
    return (0xa);
  else if (c == 'r')
    return (0xd);
  else if (c == 't')
    return (0x9);
  else if (c == 'v')
    return (0xb);
  else if (c == '\\')
    return ('\\');
  return (c);
}

void	print_char(char *c, int *i)
{
  if (c[*i] == '\\')
      if (c[++(*i)] == 'a')
        my_putchar(0x7);
      else if (c[*i] == 'b')
        my_putchar(0x8);
      else if (c[*i] == 'f')
        my_putchar(0xc);
      else if (c[*i] == 'n')
        my_putchar(0xa);
      else if (c[*i] == 'r')
        my_putchar(0xd);
      else if (c[*i] == 't')
        my_putchar(0x9);
      else if (c[*i] == 'v')
        my_putchar(0xb);
      else if (c[*i] == '\\')
	my_putchar('\\');
      else
	{
	  my_putchar('\\');
	  my_putchar(c[*i]);
	}
  else
    my_putchar(c[*i]);
}

int	echo_term(char **args)
{
  int	i;
  int	j;
  int	flag_n;

  flag_n = (args[0] && !strcmp(args[0], "-n"));
  i = flag_n - 1;
  while (args[++i])
    {
      if (i - (flag_n))
	my_putchar(' ');
      j = -1;
      while (args[i][++j])
	print_char(args[i], &j);
    }
  if (!flag_n)
    my_putchar('\n');
  return (0);
}
