/*
** alias3.c for minishell2 in /home/nicolaspolomack/shell2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat Mar 25 20:19:50 2017 Nicolas Polomack
** Last update Sun May 21 03:47:36 2017 Nicolas Polomack
*/

#include <string.h>
#include <stdlib.h>
#include "my.h"
#include "shell.h"

int	insert_alias(t_shell *shell, t_alias *e,
		     int *len, int i)
{
  char	*replace;

  len[1] = my_strlen(shell->line) - len[0] + my_strlen(e->command);
  if ((replace = malloc(len[1] + 1)) == NULL)
    handle_error("malloc");
  my_strncpy(replace, shell->line, i);
  my_strcat(replace, e->command);
  my_strcat(replace, shell->line + i + len[0]);
  free(shell->line);
  shell->line = replace;
  return (0);
}

static int	replace(char *last, int len[2],
			char *line, int *i)
{
  free(last);
  *i += (len[0] - 1);
  free(line);
  return (0);
}

int	check_alias(t_shell *shell, t_alias *e,
		    int *i, char *last)
{
  int		len[2];
  char		*line;

  len[0] = my_strstrlen(shell->line + *i, " \t><;|");
  line = my_strndup(shell->line + *i, len[0]);
  e = shell->alias;
  while (e)
    {
      if (my_strcmp(line, e->alias) == 0)
	{
	  if (detect_loop(shell, line, *i) == -1 ||
	      insert_alias(shell, e, len, *i) == -1)
	    return (-1);
	  free(last);
	  last = line;
	  len[0] = my_strstrlen(shell->line + *i, " \t><;|");
	  line = my_strndup(shell->line + *i, len[0]);
	  if (my_strcmp(line, last) == 0)
	    break;
	  e = shell->alias;
	}
      else
	e = e->next;
    }
  return (replace(last, len, line, i));
}

int		parse_alias(t_shell *shell)
{
  int		i;
  char		*last;
  int		c;
  t_alias	*e;

  i = -1;
  last = NULL;
  c = 1;
  e = NULL;
  memset((&shell->subst), 0, sizeof(t_subst));
  while (shell->line[++i])
    if (is_space(shell->line[i]) || is_separator(shell->line[i]))
      {
	while (shell->line[i] &&
	       (is_space(shell->line[i]) || is_separator(shell->line[i])))
	  if (is_delimiter(shell->line[i++]))
	    c = 1;
	i -= 1;
      }
    else if (c && !(c = 0))
      if (check_alias(shell, e, &i, last) == -1)
	return (-1);
  free_subst(shell);
  return (0);
}
