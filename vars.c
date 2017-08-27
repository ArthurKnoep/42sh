/*
** vars.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu May 18 17:26:01 2017 Nicolas Polomack
** Last update Sun May 21 04:30:06 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "my.h"
#include "shell.h"

static void	insert_line(char ***tab, char *line)
{
  char	**ret;
  int	size;

  size = ((*tab) == NULL) - 1;
  while ((*tab) && (*tab)[++size]);
  if ((ret = malloc(sizeof(char *) * (size + 2))) == NULL)
    handle_error("malloc");
  size = ((*tab) == NULL) - 1;
  while ((*tab) && (*tab)[++size])
    ret[size] = (*tab)[size];
  ret[size] = line;
  ret[++size] = NULL;
  free(*tab);
  *tab = ret;
}

void	add_var(t_shell *shell, char *name, char *value)
{
  char	*str;
  char	*tmp;
  int	i;

  if (name == NULL ||
      (tmp = my_strcatdup(name, "\t")) == NULL)
    handle_error("malloc");
  if (value && ((str = my_strcatdup(tmp, value)) == NULL))
    handle_error("malloc");
  else if (!value)
    str = tmp;
  i = -1;
  while (shell->vars && shell->vars[++i])
    if (!strncmp(shell->vars[i], name, strlen(name)) &&
	shell->vars[i][strlen(name)] == '\t')
      {
	free(shell->vars[i]);
	shell->vars[i] = (str == tmp) ? strdup(str) : str;
	return ;
      }
  insert_line(&shell->vars, (str == tmp) ? strdup(str) : str);
  free(tmp);
}

char	*get_var(t_shell *shell, char *name)
{
  int	i;
  int	size;

  if (!name)
    return (NULL);
  size = strlen(name);
  i = -1;
  while (shell->vars[++i])
    if (!strncmp(shell->vars[i], name, size) && shell->vars[i][size] == '\t')
      return (shell->vars[i] + size + 1);
  return (NULL);
}

void	init_vars(t_shell *shell)
{
  char	*str;

  shell->vars = NULL;
  if (asprintf(&str, "%d", getpid()) == -1)
    handle_error("malloc");
  add_var(shell, "pid", str);
  free(str);
  if (asprintf(&str, "%d", getgid()) == -1)
    handle_error("malloc");
  add_var(shell, "gid", str);
  free(str);
  if (asprintf(&str, "%d", getpgrp()) == -1)
    handle_error("malloc");
  add_var(shell, "pgid", str);
  free(str);
  if (asprintf(&str, "%d", getsid(0)) == -1)
    handle_error("malloc");
  add_var(shell, "sid", str);
  free(str);
}
