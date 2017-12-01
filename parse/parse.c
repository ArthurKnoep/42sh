/*
** parse.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:50:20 2017 Nicolas Polomack
** Last update Fri Nov 2 03:53:32 2017 nicolaspolomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

unsigned int	count_args(char *str)
{
  int		i;
  char		quote;
  unsigned int	args;

  i = -1;
  args = 0 + (quote = 0);
  while (str[++i])
    if (str[i] == '\\')
      i += !!(str[i + 1]);
    else if (str[i] == '\'' || str[i] == '"')
      {
	skip_string(str, &i);
	args += 1;
      }
    else if (i == 0 && str[i] != ' ' && str[i] != '\t')
      args += 1;
    else if ((str[i] != ' ' && str[i] != '\t') &&
	     (str[i - 1] == ' ' || str[i - 1] == '\t'))
      args += 1;
  return (args + 1);
}

int	get_quoted_text(char *arg, char **final, int l, char c)
{
  int	i;
  int	j;

  j = 1;
  i = -1;
  while (arg[j] != c && arg[j] != 0)
    {
      if (arg[j] == '\\')
	j += !!(arg[j]);
      j += 1;
    }
  if (arg[j++] == 0)
    return ((c == '"') ? -3 : -4);
  if ((*final = malloc(j + 1)) == NULL)
    return (-1);
  while (arg[++i + 1] != c)
    {
      if (arg[i + 1] == '\\')
	i += !!(arg[i + 2]);
      (*final)[i] = arg[i + 1];
    }
  (*final)[i] = 0;
  while (arg[j] && (arg[j] == ' ' || arg[j] == '\t'))
    j += 1;
  if (arg[j] == 0)
    return (-2);
  return (l + j);
}

int	get_next_arg(char *arg, char **final, int l)
{
  int	i;
  int	j;

  i = -1;
  j = 0;
  arg += l;
  while (*arg == ' ' || *arg == '\t')
    arg += 1;
  if (*arg == '"' || *arg == '\'')
    return (get_quoted_text(arg, final, l, *arg));
  while (arg[j] != ' ' && arg[j] != '\t' &&
	 arg[j] != '\'' && arg[j] != '"' &&
	 arg[j] != 0)
    j += 1;
  if ((*final = malloc(j + 1)) == NULL)
    return (-1);
  while (++i < j)
    (*final)[i] = arg[i];
  (*final)[i] = 0;
  while ((arg[j] == ' ' || arg[j] == '\t') && arg[j] != 0)
    j += 1;
  if (arg[j] == 0)
    return (-2);
  return (l + j);
}

int	count_entries(char *str)
{
  int	i;
  int	args;

  i = -1;
  args = 0;
  while (str[++i] != 0)
    {
      if (i == 0 && str[i] != ':')
        args += 1;
      else if (str[i] != ':' && str[i - 1] == ':')
        args += 1;
    }
  return (args);
}

int	get_next_entry(char *arg, char **final, int l)
{
  int	i;
  int	j;

  i = -1;
  j = 0;
  arg += l;
  while (*(arg) == ':')
    arg += 1;
  while (arg[++j] != ':' && arg[j] != 0);
  if ((*final = malloc(j + 1)) == NULL)
    return (-1);
  while (++i < j)
    (*final)[i] = arg[i];
  (*final)[i] = 0;
  while (arg[j] == ':' && arg[j] != 0)
    j += 1;
  if (arg[j] == 0)
    return (-2);
  return (l + j);
}
