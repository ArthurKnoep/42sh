/*
** char_double.c for char_d in /home/arthur/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <arthur@epitech.net>
** 
** Started on  Mon Jan  9 21:44:09 2017 
** Last update Thu May 18 21:46:21 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

char	**add_to_chardouble(char *str, char **list)
{
  int	i;
  char	**ret;

  if ((ret = malloc(sizeof(char *) * (nb_args(list) + 2))) == NULL)
    return (NULL);
  ret[nb_args(list) + 1] = NULL;
  i = 0;
  while (list && list[i])
    {
      ret[i] = my_strdup(list[i]);
      i += 1;
    }
  ret[i] = my_strdup(str);
  return (ret);
}
