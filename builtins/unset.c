/*
** unset.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu May 18 22:02:32 2017 Nicolas Polomack
** Last update Fri May 19 18:24:57 2017 Nicolas Polomack
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

static void	set_result(char ***tab, char *line,
			   char **ret)
{
  free(line);
  free(*tab);
  *tab = ret;
}

static void	remove_line(char ***tab, char *line)
{
  int	size;
  int	i;
  char	**ret;

  if (!*tab)
    return ;
  size = -1;
  while ((*tab)[++size]);
  if (size == 1)
    return (set_result(tab, line, NULL));
  if ((ret = malloc(sizeof(char *) * size)) == NULL)
    handle_error("malloc");
  i = 0;
  size = -1;
  while ((*tab)[++size])
    {
      if (!strcmp((*tab)[size], line))
	continue ;
      ret[i] = (*tab)[size];
      i += 1;
    }
  ret[i] = 0;
  set_result(tab, line, ret);
}

int	unset(t_shell *shell, int args)
{
  int	i;
  int	size;
  int	j;

  i = 0;
  if (args == 1)
    {
      dprintf(2, "unset: Too few arguments.\n");
      return (1);
    }
  while (shell->cur->av[++i])
    {
      if (!shell->vars)
	return (1);
      size = strlen(shell->cur->av[i]);
      j = -1;
      while (shell->vars[++j])
	if (!strncmp(shell->vars[j], shell->cur->av[i],
		     size) && shell->vars[j][size] == '\t')
	  {
	    remove_line(&shell->vars, shell->vars[j]);
	    break;
	  }
    }
  return (0);
}
