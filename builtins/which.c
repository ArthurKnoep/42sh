/*
** where.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri May 19 23:21:05 2017 Nicolas Polomack
** Last update Sun May 21 03:57:43 2017 Nicolas Polomack
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "my.h"

static int	find_first_cmd(t_shell *shell, char *str)
{
  int		i;
  int		ret;
  char		*path;
  char		*tmp;

  i = -1;
  ret = 0;
  while (!ret && shell->path[++i])
    {
      if (shell->path[i][strlen(shell->path[i])] != '/')
	tmp = my_strcatdup(shell->path[i], "/");
      else
	tmp = strdup(shell->path[i]);
      if (tmp == NULL || (path = my_strcatdup(tmp, str)) == NULL)
	handle_error("malloc");
      free(tmp);
      if (access(path, F_OK | X_OK) == 0)
	{
	  printf("%s\n", path);
	  ret = 1;
	}
      free(path);
    }
  return (ret);
}

static int	search(t_shell *shell, int i)
{
  char	*str;
  int	ret;

  ret = 1;
  if ((str = get_alias_cmd(shell, shell->cur->av[i])))
    {
      printf("%s: \t aliased to %s\n", shell->cur->av[i], str);
      free(str);
      ret = 0;
    }
  if (ret && indexof_builtin(shell->cur->av[i]) != -1)
    {
      printf("%s: shell built-in command.\n", shell->cur->av[i]);
      ret = 0;
    }
  if (ret && shell->path)
    if (find_first_cmd(shell, shell->cur->av[i]))
      ret = 0;
  if (ret == 1)
    printf("%s: Command not found.\n", shell->cur->av[i]);
  return (ret);
}

int	which(t_shell *shell, int args)
{
  int	i;
  int	ret;

  (void)args;
  i = 0;
  ret = 0;
  while (shell->cur->av[++i])
    if (is_path(shell->cur->av[i]))
      if (access(shell->cur->av[i], F_OK | X_OK) == 0)
	printf("%s\n", shell->cur->av[i]);
      else
	{
	  printf("%s: Command not found.\n", shell->cur->av[i]);
	  ret = 1;
	}
    else
      ret |= search(shell, i);
  if (i == 1)
    {
      dprintf(2, "which: Too few arguments.\n");
      return (1);
    }
  return (ret);
}
