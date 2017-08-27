/*
** stars.c for stars in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May 19 09:59:04 2017 Arthur Knoepflin
** Last update Sun May 21 04:21:52 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <stdio.h>
#include <glob.h>
#include "shell.h"
#include "my.h"

static void	skip_to_next(char *str, int *i)
{
  while (str[*i] && is_space(str[*i]))
    *i += 1;
}

static void	update_glob(t_shell *shell,
			    char *arg,
			    int *i,
			    glob_t list)
{
  char		*tmp;
  char		*file;

  file = construct_alias(list.gl_pathv);
  asprintf(&tmp, "%.*s%s%s",
	   *i, shell->line, file,
	   shell->line + *i + my_strlen(arg));
  free(shell->line);
  shell->line = tmp;
  *i += my_strlen(file);
  free(file);
  free(arg);
  free_tab(list.gl_pathv);
}

static void	glob_stars(t_shell *shell, char *arg, int *i)
{
  glob_t	list;

  if (!arg)
    {
      *i += 1;
      return ;
    }
  list.gl_offs = 1;
  glob(arg, GLOB_TILDE | GLOB_BRACE, NULL, &list);
  if (list.gl_pathc == 0)
    {
      *i += my_strlen(arg);
      free(arg);
    }
  else
    {
      update_glob(shell, arg, i, list);
    }
}

int	parse_stars(t_shell *shell)
{
  int	i;
  int	start;
  int	len;

  i = 0;
  skip_to_next(shell->line, &i);
  while (i < my_strlen(shell->line))
    {
      len = 0;
      start = i;
      while (shell->line[i + len] && !is_space(shell->line[i + len]))
	len += 1;
      glob_stars(shell, my_strndup(shell->line + start, len), &i);
      skip_to_next(shell->line, &i);
    }
  return (0);
}
