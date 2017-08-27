/*
** loop.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun May 21 02:03:23 2017 Nicolas Polomack
** Last update Sun May 21 02:05:15 2017 Nicolas Polomack
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

static int	can_replace(t_shell *shell, char *line)
{
  int		i;
  char		**ret;

  i = -1;
  while (shell->subst.list && shell->subst.list[++i])
    if (strcmp(shell->subst.list[i], line) == 0)
      return (0);
  i = (shell->subst.list == NULL) - 1;
  if (i == -1)
    while (shell->subst.list[++i]);
  if ((ret = malloc(sizeof(char **) * (i + 2))) == NULL)
    handle_error("malloc");
  i = (shell->subst.list == NULL) - 1;
  if (i == -1)
    while (shell->subst.list[++i])
      ret[i] = shell->subst.list[i];
  ret[i++] = strdup(line);
  ret[i] = NULL;
  free(shell->subst.list);
  shell->subst.list = ret;
  return (1);
}

void	free_subst(t_shell *shell)
{
  int	i;

  i = -1;
  while (shell->subst.list && shell->subst.list[++i])
    free(shell->subst.list[i]);
  free(shell->subst.list);
}

int	detect_loop(t_shell *shell, char *line, int i)
{
  if (!can_replace(shell, line) &&
      i == shell->subst.idx)
    {
      dprintf(2, "Alias loop.\n");
      return (-1);
    }
  return (0);
}
