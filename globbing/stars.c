/*
** stars.c for stars in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May 19 09:59:04 2017 Arthur Knoepflin
** Last update Fri Nov 2 03:38:07 2017 nicolaspolomack
*/

#include <stdlib.h>
#include <stdio.h>
#include <glob.h>
#include "shell.h"
#include "my.h"

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
    return ;
  list.gl_offs = 1;
  glob(arg, GLOB_TILDE | GLOB_BRACE, NULL, &list);
  if (list.gl_pathc == 0)
    {
      *i += my_strlen(arg);
      free(arg);
    }
  else
    update_glob(shell, arg, i, list);
  *i -= 1;
}

int	parse_stars(t_shell *shell)
{
  int	i;
  int	len;

  i = -1;
  while (shell->line[++i])
    if (shell->line[i] == '\\')
      i += !!(shell->line[i + 1]);
    else if (shell->line[i] == '\'' || shell->line[i] == '"')
      skip_string(shell->line, &i);
    else if (!is_space(shell->line[i]))
      {
	len = 0;
	while (shell->line[i + len] && !is_space(shell->line[i + len]))
	  len += 1;
	glob_stars(shell, my_strndup(shell->line + i, len), &i);
      }
  return (0);
}
