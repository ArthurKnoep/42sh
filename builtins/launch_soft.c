/*
** launch_soft.c for soft in /home/arthur/delivery/PSU/PSU_2016_minishell1
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Fri Jan 20 12:08:54 2017 Arthur Knoepflin
** Last update Thu May 18 23:26:39 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

int	str_in(char *str1, char *in)
{
  if (my_strncmp(str1, in, my_strlen(str1)) == 0 &&
      in[my_strlen(str1)] == '=')
    return (1);
  return (0);
}

int	nb_args_valid(t_parse_env *parse)
{
  int	i;
  int	count;

  i = 0;
  count = 0;
  while (environ && environ[i])
    {
      if (!str_in_liste(parse->unset_l, environ[i]))
	count += 1;
      i += 1;
    }
  return (count);
}

char	**getting_env(t_parse_env *parse, char **env)
{
  int	i;
  int	j;

  if (parse->ignore == 1)
    return (NULL);
  if ((env = malloc(sizeof(char *) *
		    (nb_args_valid(parse) + 1))) == NULL)
    return (NULL);
  env[nb_args_valid(parse)] = NULL;
  i = 0;
  j = 0;
  while (environ && environ[i])
    {
      if (!str_in_liste(parse->unset_l, environ[i]))
	{
	  env[j] = my_strdup(environ[i]);
	  j += 1;
	}
      i += 1;
    }
  return (env);
}

int	launch_soft(t_parse_env *parse)
{
  char	**env;

  env = NULL;
  env = getting_env(parse, env);
  if (parse->cmd != NULL)
    return (exec_arg(parse->cmd[0], parse->cmd, env));
  else
    show_tab_env(env);
  return (0);
}
