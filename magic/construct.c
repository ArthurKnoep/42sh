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
    sprintf(ret, "%s '%s'", ret, tab[i]);
  return (ret);
}
