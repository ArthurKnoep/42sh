/*
** path.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:46:13 2017 Nicolas Polomack
** Last update Sun May 21 04:24:59 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

char	*cat_path(char **path, char *final, int i)
{
  char	*str;
  char	*dir;

  if (i == -1 || i == -2)
    dir = my_strdup((i == -2) ? "/bin" : "/usr/bin");
  else if (i >= 0)
    dir = path[i];
  else
    return (NULL);
  if ((str = malloc(my_strlen(dir) + my_strlen(final) + 2)) == NULL)
    handle_error("malloc");
  *str = 0;
  str = my_strcat(str, dir);
  if (dir[my_strlen(dir)] != '/')
    str[my_strlen(dir)] = '/';
  str[my_strlen(dir) + 1] = 0;
  str = my_strcat(str, final);
  if (i < 0)
    free(dir);
  return (str);
}

int	is_path(char *str)
{
  int	i;

  i = -1;
  while (str[++i] != 0)
    if (str[i] == '/')
      return (1);
  return (0);
}

char	**init_path(char *str)
{
  char	**path;

  if (str == NULL)
    return (NULL);
  if ((path = my_split(str, ":")) == NULL)
    handle_error("malloc");
  return (path);
}

void		set_path(t_shell *shell, char *path)
{
  int		i;
  int		obj;
  char		*name;
  char		*entry;

  (void)shell;
  i = -1;
  obj = my_strlen_spe(path, '=');
  if ((name = malloc(obj + 1)) == NULL)
    handle_error("malloc");
  while (++i < obj)
    name[i] = path[i];
  name[i] = 0;
  i = obj + 1;
  obj = my_strlen_spe(path + i , '\0');
  if ((entry = malloc(obj + 1)) == NULL)
    handle_error("malloc");
  obj = i;
  i = -1;
  while ((path + obj)[++i] != 0)
    entry[i] = (path + obj)[i];
  entry[i] = 0;
  setenv(name, entry, 1);
  free(name);
  free(entry);
}

void	parse_rc(t_shell *shell)
{
  int	fd;
  char	*path;

  if (shell->home == NULL)
    return ;
  if ((path = malloc(512)) == NULL)
    handle_error("malloc");
  path[0] = 0;
  path = my_strcat(path, shell->home);
  if (shell->home[my_strlen(shell->home)] != '/')
    path[my_strlen(shell->home)] = '/';
  path[my_strlen(shell->home) + 1] = 0;
  path = my_strcat(path, RC_FILE);
  if ((fd = open(path, O_RDONLY)) == -1)
    return ;
  free(path);
  while ((path = get_next_line(fd)) != NULL)
    {
      if (is_valid_path(path))
        set_path(shell, path);
      free(path);
    }
  close(fd);
}
