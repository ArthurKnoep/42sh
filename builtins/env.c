/*
** env.c for env in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May 18 11:01:26 2017 Arthur Knoepflin
** Last update Thu May 18 23:26:51 2017 Arthur Knoepflin
*/

#include "shell.h"
#include "builtin.h"
#include "my.h"

void	show_tab_env(char **env)
{
  int	i;

  i = 0;
  while (env && env[i])
    {
      my_printf("%s\n", env[i]);
      i += 1;
    }
}

void	show_env(void)
{
  int	i;

  i = 0;
  while (environ && environ[i])
    {
      my_printf("%s\n", environ[i]);
      i += 1;
    }
}

int		env_b(t_shell *shell, int args)
{
  t_parse_env	*parse;

  if (args == 1)
    show_env();
  else
    {
      if ((parse = parse_env(shell->cur->av)) == NULL)
	return (1);
      if (parse->null == 1 && parse->cmd != NULL)
      	my_puterror("env: cannot specify --null (-0) with command.\n");
      else if (parse->null == 1 && parse->cmd == NULL)
      	show_env_parse(parse);
      else
      	return (launch_soft(parse));
    }
  return (0);
}
