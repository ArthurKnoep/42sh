/*
** check.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Jan  9 10:55:14 2017 Nicolas Polomack
** Last update Sun May 21 04:33:47 2017 Nicolas Polomack
*/

#include <string.h>
#include <stdlib.h>
#include "my.h"
#include "shell.h"

char	*my_epurstr(char *str)
{
  char	*ret;
  int	i[2];
  char	b;

  i[0] = -1 + (i[1] = 0) + (b = 0);
  if ((ret = malloc(my_strlen(str) + 1)) == NULL)
    return (NULL);
  while (str[++(i[0])])
    {
      if (!(i[0] == 0 && (str[i[0]] == ' ' || str[i[0]] == '\t')))
	ret[i[1]++] = ((str[i[0]] == '\t') ? ' ' : str[i[0]]);
      if (!b && (str[i[0]] == ' ' || str[i[0]] == '\t'))
	{
	  while (str[i[0]] && (str[i[0]] == ' ' || str[i[0]] == '\t'))
	    i[0] += 1;
	  i[0] -= 1;
	}
      else if (str[i[0]] == b && b != 0)
	b = 0;
      else if ((str[i[0]] == '\'' || str[i[0]] == '"') && b == 0)
	b = str[i[0]];
    }
  ret[i[1]] = 0;
  free(str);
  return (ret);
}

int	count_links(char *str)
{
  int	i;
  int	count;
  char	buf;

  i = -1;
  count = 0;
  while (str[++i])
    {
      if (str[i] == '\\')
        i += !!(str[i + 1]);
      else if (str[i] == '\'' || str[i] == '"')
	{
	  buf = str[i];
	  i += 1;
	  while (str[i] && str[i] != buf)
	    i += (str[i] == '\\') + 1;
	  if (str[i] == 0)
	    {
	      my_putchar_fd(buf, 2);
	      return (my_print_ret(": Invalid quotes.\n", -1));
	    }
	}
      count += is_separator(str[i]);
    }
  return (count);
}

void	skip_and_copy_string(char *str, int *i, char *ret, int *t)
{
  char	quote;

  quote = str[(*i)++];
  ret[(*t)++] = quote;
  while (str[*i] && str[*i] != quote)
    {
      if (str[*i] == '\\')
	{
	  ret[(*t)++] = '\\';
	  ret[(*t)++] = str[(*i) + 1];
	  *i += !!(str[(*i) + 1]);
	}
      else
	ret[(*t)++] = str[*i];
      *i += 1;
    }
  ret[(*t)++] = str[(*i)];
}

void	copy_escaped_char(char *str, int *i, char *ret, int *t)
{
  ret[(*t)++] = '\\';
  ret[(*t)++] = str[(*i) + 1];
  *i += !!(str[(*i) + 1]);
}

char	*my_epurcommand(char *str)
{
  char	*ret;
  int	i;
  int	t;

  if ((i = count_links(str)) == -1 ||
      (ret = malloc(strlen(str) + 1 + i * 4)) == NULL)
    return (NULL);
  i = -1 + (t = 0);
  while (str[++i])
    {
      if (str[i] == '\\')
	copy_escaped_char(str, &i, ret, &t);
      else if (is_space(str[i]))
        {
	  ret[t++] = ' ';
	  while (is_space(str[++i]));
	  i -= 1;
	}
      else if (str[i] == '"' || str[i] == '\'')
        skip_and_copy_string(str, &i, ret, &t);
      else if (is_separator(str[i]))
        {
	  ret[t++] = ' ';
	  ret[t++] = str[i];
	  ret[t++] = ' ';
	}
      else
        ret[t++] = str[i];
    }
  free(str + (ret[t] = 0));
  return (ret);
}
