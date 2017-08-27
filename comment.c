/*
** comment.c for comment in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May 18 19:11:24 2017 Arthur Knoepflin
** Last update Thu May 18 20:57:35 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "shell.h"
#include "my.h"

int	clear_comment(t_shell *shell)
{
  int	i;
  int	quote;
  char	*tmp;

  i = 0;
  quote = 0;
  while (shell->line[i])
    {
      if (shell->line[i] == '\'' && (quote == 0 || quote == 1))
	quote = (quote == 0) ? 1 : 0;
      if (shell->line[i] == '"' && (quote == 0 || quote == 2))
	quote = (quote == 0) ? 2 : 0;
      if (shell->line[i] == '#' && quote == 0 &&
	  (i == 0 || (i != 0 && (shell->line[i - 1] == ' '))))
	{
	  tmp = my_strndup(shell->line, i);
	  free(shell->line);
	  shell->line = tmp;
	  return (0);
	}
      i += 1;
    }
  return (0);
}
