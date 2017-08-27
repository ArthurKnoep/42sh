/*
** env_cherror_2.c for env_cherror_2 in /home/arthur/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <arthur@epitech.net>
** 
** Started on  Mon Jan  9 19:18:26 2017 
** Last update Thu May 18 21:22:18 2017 Arthur Knoepflin
*/

#include "shell.h"
#include "builtin.h"
#include "my.h"

static int	is_valid(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (!((str[i] >= 'a' && str[i] <= 'z') ||
	    (str[i] >= 'A' && str[i] <= 'Z') ||
	    (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
	return (0);
      i += 1;
    }
  return (1);
}

int	is_alpha_err(char *lines, int size)
{
  if (!is_valid(lines + size))
    {
      my_puterror(my_fstrcat(my_fstrcat("env: cannot unset '",
					lines + size, 0),
			     "': Invalid argument\n", 0));
      return (1);
    }
  return (0);
}
