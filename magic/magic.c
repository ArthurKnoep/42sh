/*
** magic.c for 42sh in /home/nicolaspolomack/TurboSh/magic
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat May 20 02:34:26 2017 Nicolas Polomack
** Last update Mon May 22 14:35:15 2017 Nicolas Polomack
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#include "shell.h"

static int	get_len(t_shell *shell, int i)
{
  long int	str;

  if ((str = (long int)strstr(shell->line + i + 1, "`")) == 0)
    {
      dprintf(2, "Unmatched '`'.\n");
      return (-1);
    }
  str -= ((long int)shell->line) + i + 1;
  return ((int)str);
}

static void	insert_inline(t_shell *shell, char **buffer,
			      int i, int len)
{
  char		*result;
  char		*ret;
  int		l[2];

  if (buffer)
    {
      l[1] = -1;
      while (buffer[++(l[1])])
	{
	  l[0] = -1;
	  while (buffer[l[1]][++l[0]])
	    buffer[l[1]][l[0]] = (buffer[l[1]][l[0]] == '\'') ?
	      '"' : buffer[l[1]][l[0]];
	}
      result = construct_magic(buffer);
      if ((asprintf(&ret, "%.*s%s%s", i, shell->line, result,
		    shell->line + i + len + 2)) == -1)
	handle_error("malloc");
    }
  else if ((asprintf(&ret, "%.*s%s", i, shell->line,
		     shell->line + i + len + 2)) == -1)
    handle_error("malloc");
  free(shell->line);
  shell->line = ret;
}

static void	add_line(char ***buffer, int *size, char *str)
{
  if (((*buffer) = realloc(*buffer, sizeof(char *) *
			   ++(*size))) == NULL)
    handle_error("malloc");
  (*buffer)[(*size) - 2] = str;
  (*buffer)[(*size) - 1] = NULL;
}

static void	exec_magic(t_shell *shell, char *line, int i, int len)
{
  int		save;
  char		**buffer;
  char		*str;
  int		size;
  int		fds[2];

  if ((save = dup(1)) == -1 ||
      pipe(fds) == -1 || dup2(fds[1], 1) == -1)
    handle_error("magic");
  close(fds[1]);
  quick_exec(shell, line);
  buffer = NULL;
  size = 1;
  if (dup2(save, 1) == -1)
    handle_error("magic");
  close(save);
  while ((str = get_next_line(fds[0])))
    add_line(&buffer, &size, str);
  close(fds[0]);
  insert_inline(shell, buffer, i, len);
  save = -1;
  while (buffer && buffer[++save])
    free(buffer[save]);
  free(buffer);
}

int		magic(t_shell *shell)
{
  int		i;
  int		len;
  char		*line;

  i = -1;
  while (shell->line[++i])
    if (shell->line[i] == '\'' || shell->line[i] == '"')
      {
	len = shell->line[i++];
	while (shell->line[i] && shell->line[i] != len)
	  i += -1;
	i -= (shell->line[i] == 0);
      }
    else if (shell->line[i] == '`')
      {
	if ((len = get_len(shell, i)) >= 0)
	  {
	    line = strndup(shell->line + i + 1, len);
	    exec_magic(shell, line, i, len);
	    i = -1;
	  }
	else if (len == -1)
	  return (-1);
      }
  return (0);
}
