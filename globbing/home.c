/*
** home.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat May 13 21:14:22 2017 Nicolas Polomack
** Last update Fri Nov 2 03:40:24 2017 nicolaspolomack
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

static int	skip_spaces(t_shell *shell, int *i)
{
  while (is_space(shell->line[*i]))
    *i += 1;
  *i -= 1;
  return (1);
}

static void	insert_home(t_shell *shell, int i)
{
  int		ret;
  char		*str;

  ret = asprintf(&str, "%.*s%s%s", i, shell->line, shell->home,
               shell->line + i + 1);
  if (ret == -1 || str == NULL)
    handle_error("malloc");
  free(shell->line);
  shell->line = str;
}

void	skip_string(char *str, int *i)
{
  char		quote;

  quote = str[(*i)++];
  while (str[*i] && str[*i] != quote)
    *i += 1;
  *i -= (str[*i] == 0);
}

void	replace_home(t_shell *shell)
{
  int	i;

  if (shell->home == NULL)
    return ;
  i = -1;
  while (shell->line[++i])
    if (shell->line[i] == '\\')
      i += !!(shell->line[i + 1]);
    else if (is_space(shell->line[i]))
      skip_spaces(shell, &i);
    else if (shell->line[i] == '\'' || shell->line[i] == '"')
      skip_string(shell->line, &i);
    else if (shell->line[i] == '~')
      insert_home(shell, i);
}
