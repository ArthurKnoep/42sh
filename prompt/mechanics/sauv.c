/*
** sauv.c for sauv_prompt in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May 12 21:48:18 2017 Arthur Knoepflin
** Last update Wed May 17 12:54:57 2017 Arthur Knoepflin
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "get_next_line.h"
#include "my.h"

static char	**add_to_cdouble(char *str, char **list)
{
  int		i;
  char		**ret;

  if ((ret = malloc(sizeof(char *) * (nb_args(list) + 2))) == NULL)
    return (NULL);
  ret[nb_args(list) + 1] = NULL;
  i = 0;
  while (list && list[i])
    {
      ret[i] = strdup(list[i]);
      free(list[i]);
      i += 1;
    }
  ret[i] = strdup(str);
  free(list);
  return (ret);
}

static void	update_prompt(char ***file, t_shell *shell)
{
  int		stop;
  char		*add;
  int		i;

  if (asprintf(&add, "PROMPT=%d", shell->prompt) == -1)
    handle_error("malloc");
  i = 0;
  stop = 0;
  while ((*file)[i])
    {
      if (!my_strncmp("PROMPT=", (*file)[i], 7))
	{
	  free((*file)[i]);
	  (*file)[i] = strdup(add);
	  stop = 1;
	}
      i += 1;
    }
  if (!stop)
    (*file) = add_to_cdouble(add, *file);
  free(add);
}

static void	write_file(char **env)
{
  int		i;
  int		fd;
  char		*path;
  char		*str;

  if ((path = my_strcatdup(get_env("HOME"), "/")) == NULL)
    return ;
  if ((fd = open(str = my_strcatdup(path, RC_FILE),
		 O_WRONLY | O_TRUNC | O_CREAT)) == -1)
    return ;
  free(path);
  free(str);
  i = 0;
  while (env[i])
    {
      dprintf(fd, "%s\n", env[i]);
      i += 1;
    }
  free_tab(env);
  close(fd);
}

void	sauv_prompt(t_shell *shell)
{
  char	*home;
  char	*path;
  char	*str;
  char	**file;
  int	fd;

  if (!(home = get_env("HOME")))
    return ;
  if ((path = my_strcatdup(home, "/")) == NULL)
    return ;
  if ((fd = open(str = my_strcatdup(path, RC_FILE), O_RDONLY)) == -1)
    return ;
  free(path);
  free(str);
  if ((file = load_file(fd)) == NULL)
    {
      close(fd);
      return ;
    }
  close(fd);
  update_prompt(&file, shell);
  write_file(file);
}
