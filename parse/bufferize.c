/*
** bufferize.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:55:14 2017 Nicolas Polomack
** Last update	Thu May 18 22:55:01 2017 Full Name
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "auto_complete.h"
#include "get_next_line.h"

int	count_real_chars(char *str)
{
  int	i;
  int	c;

  i = -1;
  c = 0;
  while (str[++i])
    {
      if (str[i] == '\\')
	i += !!(str[i + 1]);
      c += 1;
    }
  return (c);
}

char	*unquote_arg(char *str)
{
  char	*ret;
  int	len;

  len = my_strlen(str) - 2;
  if ((ret = my_strndup(str + 1, len)) == NULL)
    return (NULL);
  free(str);
  return (ret);
}

char	*format_arg(char *str)
{
  int	i1;
  int	i2;
  char	*ret;

  i1 = -1;
  i2 = 0;
  if (str[i1 + 1] == '"' || str[i1 + 1] == '\'')
    str = unquote_arg(str);
  if ((ret = malloc(sizeof(char) * (count_real_chars(str) + 1))) == NULL)
    return (NULL);
  while (str[++i1])
    if (str[i1] == '\\')
      if (str[i1 + 1] == 0)
	return (NULL);
      else
	{
	  i1 += !!(str[i1 + 1]);
	  ret[i2++] = str[i1];
	}
    else
      ret[i2++] = str[i1];
  ret[i2] = 0;
  free(str);
  return (ret);
}

int	arg_length(char *str)
{
  int	i;
  char	quote;

  i = 0;
  if (str[i] == '"' || str[i] == '\'')
    {
      quote = str[i++];
      while (str[i] && str[i] != quote)
        {
	  if (str[i] == '\\')
	    i += !!(str[i + 1]);
	  i += 1;
	}
      return ((str[i] == 0) ? -1 : (i + 1));
    }
  while (str[i] && !is_space(str[i]))
    {
      if (str[i] == '\\')
	i += !!(str[i + 1]);
      i += 1;
    }
  return (i);
}

char	**bufferize(char *str, int n)
{
  int	i;
  int	args;
  char	**final;
  int	len;

  args = 0;
  i = 0;
  if ((final = malloc(sizeof(char *) * (n + 1))) == NULL)
    return (NULL);
  while (str[i])
    if (is_space(str[i]))
      i += 1;
    else
      {
	if ((len = arg_length(str + i)) == -1 ||
	    (final[args] = my_strndup(str + i, len)) == NULL)
	  return (NULL);
	i += len;
	args += 1;
      }
  final[args] = NULL;
  return (final);
}

int	count_link(char **final)
{
  int	i;

  i = 0;
  while (final[i] && (my_strcmp(final[i], "|") &&
		      my_strcmp(final[i], ";") &&
		      my_strcmp(final[i], "||") &&
		      my_strcmp(final[i], "&&")))
    i += 1;
  return (i);
}

void	prepare_link(t_shell *shell, t_command *elem, int i, int last)
{
  if (shell->final[i] == NULL)
    elem->link = '0';
  else if (my_strcmp(shell->final[i], "&&") == 0)
    elem->link = 'e';
  else if (my_strcmp(shell->final[i], "||") == 0)
    elem->link = 'o';
  else
    elem->link = shell->final[i][0];
  shell->final[i] = NULL;
  elem->av = my_strarrdup(shell->final + last);
  (elem->link != '0') ? insert_char(&(shell->final[i]), elem->link) : NULL;
  elem->count = -1;
}

int		set_commands(t_shell *shell)
{
  t_command	*elem;
  t_command	*head;
  int		i;
  int		last;

  shell->commands = NULL;
  head = NULL;
  i = -1;
  while (shell->final[++i])
    {
      if ((elem = malloc(sizeof(*elem))) == NULL)
	return (-1);
      elem->next = NULL;
      (head) ? (head->next = elem) : (shell->commands = elem);
      elem->prev = head;
      last = i;
      if ((i += count_link(shell->final + i)) == last)
	return (ret_error(shell, "Invalid null command.\n"));
      prepare_link(shell, elem, i, last);
      i -= (elem->link == '0');
      head = elem;
    }
  return (0);
}
