/*
** env2.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 11:01:50 2017 Nicolas Polomack
** Last update Thu May 18 20:56:33 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

int	disp_env()
{
  int	i;

  i = -1;
  while (environ[++i] != NULL)
    my_printf("%s\n", environ[i]);
  return (0);
}

int	check_env_error(char *mod, char *name)
{
  if (name[0] == 0 || ((name[0] < 'a' || name[0] > 'z') &&
                       (name[0] < 'A' || name[0] > 'Z')))
    return (dprintf(2, "%s: Variable name must \
begin with a letter.\n", mod));
  if (!is_char_alpha(name))
    return (dprintf(2, "%s: Variable name must \
contain alphanumeric characters.\n", mod));
  return (0);
}
