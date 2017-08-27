/*
** show_env_parse.c for show_env in /home/arthur/delivery/PSU/PSU_2016_minishell1
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Fri Jan 20 13:42:01 2017 Arthur Knoepflin
** Last update Thu May 18 23:00:35 2017 Arthur Knoepflin
*/

#include <unistd.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

int	str_in_liste(char **str1, char *in)
{
  int	i;

  i = 0;
  while (i < nb_args(str1))
    {
      if (my_strncmp(str1[i], in, my_strlen(str1[i])) == 0 &&
	  in[my_strlen(str1[i])] == '=')
	return (1);
      i += 1;
    }
  return (0);
}

void	show_env_parse(t_parse_env *parse)
{
  int	i;

  i = 0;
  if (parse->ignore == 1)
    return ;
  else
    {
      while (environ && environ[i])
	{
	  if (!str_in_liste(parse->unset_l, environ[i]))
	    my_printf("%s", environ[i]);
	  i += 1;
	}
    }
}
