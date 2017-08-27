/*
** set.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu May 18 20:41:29 2017 Nicolas Polomack
** Last update Sun May 21 03:56:05 2017 Nicolas Polomack
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "my.h"

int	disp_vars(t_shell *shell)
{
  int	i;

  i = -1;
  if (shell->vars)
    while (shell->vars[++i])
      {
	my_putstr(shell->vars[i]);
	my_putchar(0xa);
      }
  return (0);
}

int	set(t_shell *shell, int args)
{
  char	*str;
  char	*comp;
  int	i;
  int	ret;

  if (args == 1)
    return (disp_vars(shell));
  else
    {
      ret = 0;
      i = 0;
      while (shell->cur->av[++i])
	{
	  if ((str = strdup(shell->cur->av[i])) == NULL
	      || (comp = strsep(&str, "=")) == NULL)
	    handle_error("malloc");
	  if (check_env_error("set", comp))
	    ret = 1;
	  else
	    add_var(shell, comp, str);
	  free(comp);
	}
    }
  return (ret);
}
