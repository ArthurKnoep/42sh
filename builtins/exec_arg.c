/*
** exec_arg.c for exec_arg in /home/arthur/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <arthur@epitech.net>
** 
** Started on  Sat Jan  7 16:56:08 2017 
** Last update Thu May 18 23:09:37 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

int	is_in_env(char *str, char c)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] == c)
	return (1);
      i += 1;
    }
  return (0);
}

void	free_char_double(char **ch)
{
  int	i;

  i = 0;
  while (ch && ch[i])
    {
      free(ch[i]);
      i += 1;
    }
  free(ch);
}

static char	**get_def_path(void)
{
  char	**ret;

  if ((ret = malloc(sizeof(char *) * 3)) == NULL)
    return (NULL);
  ret[2] = NULL;
  ret[0] = my_strdup("/bin");
  ret[1] = my_strdup("/usr/bin");
  return (ret);
}

int	exec_path(char *cmd, char **arg, char **ae)
{
  int	i;
  char	**l_path;
  char	*path;
  char	*tmp;

  path = getenv("PATH");
  if (path != NULL)
    l_path = my_split_char(path, ':');
  else
    l_path = get_def_path();
  i = 0;
  while (l_path && l_path[i])
    {
      if (l_path[i][my_strlen(l_path[i]) - 1] != '/')
	tmp = my_strcatdup(l_path[i], "/");
      else
	tmp = my_strdup(l_path[i]);
      if (print_error_path(my_strcatdup(tmp, cmd)))
	return (2);
      if ((execve(my_strcatdup(tmp, cmd), arg, ae)) != -1)
	return (1);
      i += 1;
    }
  free_char_double(l_path);
  return (0);
}

int	exec_arg(char *cmd, char **arg, char **ae)
{
  int	pid;
  int	ret;

  pid = fork();
  if (pid == 0)
    {
      if (is_in_env(cmd, '/'))
	{
	  exec_not_path(cmd, arg, ae);
	  exit(1);
	}
      else
	{
	  ret = exec_path(cmd, arg, ae);
	  if (ret == 0)
	    my_puterror(my_strcatdup(cmd, ": Command not found.\n"));
	  exit(1);
	}
    }
  else
    return (show_signal(pid));
  return (1);
}
