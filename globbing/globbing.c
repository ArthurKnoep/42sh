/*
** globbing.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:57:32 2017 Nicolas Polomack
** Last update Fri Nov 2 03:44:56 2017 nicolaspolomack
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

static int	get_arg(t_shell *shell,
			 char **str,
			 int *cur)
{
  int		nb;
  int		len;
  int		i;

  nb = my_getnbr(shell->line + *cur + 1);
  len = 0;
  while (shell->line[*cur + 1 + len] &&
  	 shell->line[*cur + 1 + len] >= '0' &&
  	 shell->line[*cur + 1 + len] <= '9')
    len += 1;
  i = asprintf(str, "%.*s%s%s", *cur, shell->line,
	       (shell->av && nb < nb_args(shell->av)) ?
	       shell->av[nb] : "",
	       shell->line + *cur + len + 1);
  return (i);
}

static char	*get_gvar(char *str)
{
  int	i;

  i = 0;
  while (str[i] && is_alphanum(str[i]))
    i += 1;
  return (strndup(str, i));
}

static void	final_checks(t_shell *shell, char *str, int *cur, int i)
{
  if (i == -1 || str == NULL)
    handle_error("malloc");
  *cur += (strlen(str) - strlen(shell->line)) + 1;
  free(shell->line);
  shell->line = str;
}

static int	replace_var(t_shell *shell, int *cur, char *var)
{
  char	*str;
  int	i;

  i = 0;
  if (!strncmp(shell->line + *cur, "$?", 2))
    i = asprintf(&str, "%.*s%d%s", *cur, shell->line, shell->exit,
		 shell->line + *cur + 2);
  else if (!strncmp(shell->line + *cur, "$$", 2))
    i = asprintf(&str, "%.*s%d%s", *cur, shell->line, getpid(),
		 shell->line + *cur + 2);
  else if (get_var(shell, var))
    i = asprintf(&str, "%.*s%s%s", *cur, shell->line, get_var(shell, var),
                 shell->line + *cur + strlen(var) + 1);
  else if (getenv(var))
    i = asprintf(&str, "%.*s%s%s", *cur, shell->line, getenv(var),
                 shell->line + *cur + strlen(var) + 1);
  else if (shell->line[*cur + 1] >= '0' && shell->line[*cur + 1] <= '9')
    i = get_arg(shell, &str, cur);
  else
    {
      dprintf(2, "%s: Undefined variable.\n", var);
      return (-1);
    }
  final_checks(shell, str, cur, i);
  return (0);
}

int	parse_vars(t_shell *shell)
{
  int	cur;
  int	is_free;
  char	*var;

  cur = -1;
  is_free = 1;
  while (shell->line[++cur])
    if (shell->line[cur] == '\\')
      cur += !!(shell->line[cur + 1]);
    else if (shell->line[cur] == '\'' && is_free)
      while (shell->line[cur + 1] && shell->line[cur + 1] != '\'')
	cur += 1;
    else if (shell->line[cur] == '"')
      is_free = !is_free;
    else if (shell->line[cur] == '$' && shell->line[cur + 1]
	     && !is_separator(shell->line[cur + 1]) &&
	     shell->line[cur + 1] != '"')
      {
	if ((var = get_gvar(shell->line + cur + 1)) == NULL)
	  exit(84);
	if (replace_var(shell, &cur, var) == -1)
	  return (-1);
      }
  return (0);
}
