/*
** env.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:59:59 2017 Nicolas Polomack
** Last update	Tue May 09 22:02:30 2017 Full Name
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

int	set_env(char *name, char *value)
{
  if (check_env_error("setenv", name))
    return (1);
  return ((!setenv(name, value, 1)) ? 0 : -1);
}

int	unset_env(char **names)
{
  int	ret;
  int	i;

  ret = 0;
  i = 0;
  while (names[++i])
    ret |= unsetenv(names[i]);
  return (ret);
}
