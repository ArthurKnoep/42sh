/*
** char.c for minishell2 in /home/nicolaspolomack/psu/2/PSU_2016_minishell2
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Thu Mar 23 10:29:41 2017 Nicolas Polomack
** Last update	Tue May 09 23:28:00 2017 Full Name
*/

#include <string.h>
#include <stdlib.h>
#include "shell.h"

void	insert_char_cur(char **str, char c, int cur)
{
  int	i;
  char	*new;

  i = -1;
  if (*str == NULL)
    i = 0;
  else
    while ((*str)[++i]);
  if ((new = malloc(i + 2)) == NULL)
    return ;
  i = 0;
  while (*str && i < cur && (*str)[i])
    {
      new[i] = (*str)[i];
      i += 1;
    }
  new[i] = c;
  while (*str && (*str)[i])
    {
      new[i + 1] = (*str)[i];
      i += 1;
    }
  new[i + 1] = 0;
  free(*str);
  *str = new;
}

void	delete_char(char **str, int cur)
{
  int	i;
  int	c;
  char	*new;

  if (*str == NULL)
    return ;
  i = strlen(*str);
  if (i == 0)
    return ;
  if ((new = malloc(i)) == NULL)
    handle_error("malloc");
  c = -1;
  while (++c < (cur - 1))
    new[c] = (*str)[c];
  while ((c + 1) < i)
    {
      new[c] = (*str)[c + 1];
      c += 1;
    }
  new[c] = 0;
  free(*str);
  *str = new;
}
