/*
** buffer.c for minishell2 in /home/nicolaspolomack/psu/2/PSU_2016_minishell2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun Mar 26 18:28:03 2017 Nicolas Polomack
** Last update Thu Apr  6 11:52:41 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "shell.h"
#include "my.h"

int	buffer_input(char *name, int i[2])
{
  char	*str;
  char	c;

  str = NULL;
  c = 10;
  while ((str = get_next_line(0)))
    if (str && my_strcmp(str, name) == 0)
      {
	free(str);
	close(i[1]);
	return (i[0]);
      }
    else
      {
	write(i[1], str, my_strlen(str));
	write(i[1], &c, 1);
	free(str);
	my_putstr(isatty(0) ? "$> " : "");
      }
  close(i[1]);
  return (i[0]);
}
