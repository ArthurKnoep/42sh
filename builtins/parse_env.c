/*
** parse_env.c for parse_env in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May 18 21:01:47 2017 Arthur Knoepflin
** Last update Thu May 18 23:37:00 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

int	nb_args_env(char **cmd)
{
  int	i;

  i = 1;
  while (cmd[i] && cmd[i][0] == '-')
    {
      if (is_in_env(cmd[i], 'u') && my_strcmp(cmd[i], "--null") &&
	  my_strncmp(cmd[i], "--unset=", 8))
	i += 1;
      i += 1;
    }
  return (i);
}

static void	fill_stru_2(char **cmd, t_parse_env *ret, int *i)
{
  if (is_in_env(cmd[*i], 'u'))
    {
      (*i) += 1;
      ret->unset_l = add_to_chardouble(cmd[*i], ret->unset_l);
      ret->unset = 1;
    }
  if (is_in_env(cmd[*i], '0'))
    ret->null = 1;
  if (is_in_env(cmd[*i], 'i'))
    ret->ignore = 1;
}

static void	fill_stru_1(char **cmd, t_parse_env *ret)
{
  int		i;

  i = 0;
  while (++i && cmd[i] && cmd[i][0] == '-')
    {
      if (my_strncmp(cmd[i], "--unset=", 8) == 0)
	{
	  ret->unset_l = add_to_chardouble(cmd[i] + 8, ret->unset_l);
	  ret->unset = 1;
	}
      else if (my_strcmp(cmd[i], "--null") == 0)
	ret->null = 1;
      else if (my_strcmp(cmd[i], "--ignore-environment") == 0)
	ret->ignore = 1;
      else
	fill_stru_2(cmd, ret, &i);
    }
}

t_parse_env	*parse_env(char **cmd)
{
  t_parse_env	*ret;

  if ((ret = malloc(sizeof(*ret))) == NULL)
    return (NULL);
  if (cherror_env_parse(cmd))
    return (NULL);
  ret->ignore = 0;
  ret->null = 0;
  ret->unset = 0;
  ret->unset_l = NULL;
  fill_stru_1(cmd, ret);
  ret->cmd = NULL;
  if (nb_args_env(cmd) != nb_args(cmd))
    ret->cmd = cmd + nb_args_env(cmd);
  else
    ret->cmd = NULL;
  return (ret);
}
