/*
** env_checkerr.c for env_cherrr.c in /home/arthur/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <arthur@epitech.net>
** 
** Started on  Mon Jan  9 10:16:31 2017 
** Last update Thu May 18 21:29:10 2017 Arthur Knoepflin
*/

#include "shell.h"
#include "builtin.h"
#include "my.h"

static int	is_an_arg(char *str)
{
  if (!my_strcmp(str, "-i") || !my_strcmp(str, "--ignore-environment"))
    return (1);
  if (!my_strcmp(str, "-0") || !my_strcmp(str, "--null"))
    return (1);
  if (!my_strcmp(str, "-i0") || !my_strcmp(str, "-0i"))
    return (1);
  if (!my_strcmp(str, "-u") || !my_strncmp(str, "--unset=", 8))
    return (1);
  return (0);
}

static int	check_arg(char **cmd)
{
  int		i;

  i = 1;
  while (cmd[i] && cmd[i][0] == '-')
    {
      if (!is_an_arg(cmd[i]))
	{
	  my_puterror(my_fstrcat(my_fstrcat("env: invalid\
 option -- '", cmd[i] + 1, 0), "'\n", 0));
	  return (1);
	}
      if (is_in_env(cmd[i], 'u') && my_strncmp(cmd[i], "--unset=", 8) &&
	  my_strcmp(cmd[i], "--null"))
	i += 1;
      i += 1;
    }
  return (0);
}

static int	check_len_arg(char **cmd)
{
  int		i;

  i = 1;
  while (cmd[i] && cmd[i][0] == '-')
    {
      if (my_strlen(cmd[i]) == 1)
	{
	  my_puterror("env : invalid option -- ''\n");
	  return (1);
	}
      if (my_strcmp(cmd[i], "-u") == 0)
	{
	  i += 1;
	  if (!cmd[i])
	    {
	      my_puterror("env: option requires an argument -- 'u'\n");
	      return (1);
	    }
	}
      i += 1;
    }
  return (0);
}

static int	check_unset(char **cmd)
{
  int		i;

  i = 0;
  while (++i && cmd[i] && cmd[i][0] == '-')
    {
      if (my_strncmp(cmd[i], "--unset=", 8) == 0)
	{
	  if (my_strlen(cmd[i]) == 8)
	    {
	      my_puterror("env: cannot unset '': Invalid argument\n");
	      return (1);
	    }
	  if (is_alpha_err(cmd[i], 8))
	    return (1);
	}
      else if (is_in_env(cmd[i], 'u') && my_strcmp(cmd[i], "--null"))
	{
	  i += 1;
	  if (is_alpha_err(cmd[i], 0))
	    return (1);
	}
    }
  return (0);
}

int	cherror_env_parse(char **cmd)
{
  if (check_len_arg(cmd))
    return (1);
  if (check_arg(cmd))
    return (1);
  if (check_unset(cmd))
    return (1);
  return (0);
}
