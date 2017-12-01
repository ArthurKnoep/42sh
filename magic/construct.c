/*
** construct.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun May 21 05:03:54 2017 Nicolas Polomack
** Last update Sun May 21 05:06:47 2017 Nicolas Polomack
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "my.h"

int	count_separators(char *str)
{
  int	i;
  int	count;

  i = -1;
  count = 0;
  while (str[++i])
    if (str[i] == '\\')
      i += !!(str[i + 1]);
    else if (is_separator(str[i]))
      count += 1;
  return (count);
}

char	*sanitize(char *str)
{
  int	i1;
  int	i2;
  int	size;
  char	*ret;

  i1 = -1;
  i2 = 0;
  size = count_separators(str);
  if ((ret = malloc(strlen(str) + (size * 2) + 1)) == NULL)
    return (NULL);
  while (str[++i1])
    if (str[i1] == '\\' || is_separator(str[i1]) || str[i1] == '"' ||
	str[i1] == '\'' || is_space(str[i1]))
      {
	ret[i2++] = '\\';
	ret[i2++] = str[++i1];
      }
    else
      ret[i2++] = str[i1];
  ret[i2] = 0;
  free(str);
  return (ret);
}

char	*construct_magic(char **tab)
{
  int		i;
  int		len;
  char		*ret;

  len = 0;
  i = -1;
  while (tab[++i])
    len += ((!!i) + strlen(tab[i]) + 2);
  if ((ret = malloc(len + 1)) == NULL)
    handle_error("malloc");
  *ret = 0;
  i = -1;
  while (tab[++i])
    {
      if (i)
	strcat(ret, " ");
      strcat(ret, tab[i]);
    }
  return (ret);
}
