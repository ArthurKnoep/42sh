/*
** alias.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:38:06 2017 Nicolas Polomack
** Last update Sun May 21 19:50:02 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

int	is_valid_alias(char *path)
{
  int	i;

  i = 0;
  if (path[i++] != 'a' || path[i++] != 'l' || path[i++] != 'i' ||
      path[i++] != 'a' || path[i++] != 's' || path[i++] != ' ')
    return (0);
  while (path[i] != '=')
    if (path[i++] == 0)
      return (0);
  if (path[++i] != '\'')
    return (0);
  while (path[++i] != '\'')
    if (path[i] == 0)
      return (0);
  if (path[++i] == 0)
    return (1);
  return (0);
}

void	write_alias(t_alias *head, int fd)
{
  my_print_fd("alias ", fd);
  my_print_fd(head->alias, fd);
  my_print_fd("='", fd);
  my_print_fd(head->command, fd);
  my_print_fd("'\n", fd);
}

void		save_alias(t_shell *shell)
{
  t_alias	*head;
  int		fd;
  char		*path;

  if (!(shell->tty)|| (shell->home == NULL) ||
      (path = malloc(512)) == NULL)
    return ;
  path[0] = 0;
  path = my_strcat(path, shell->home);
  if (shell->home[my_strlen(shell->home)] != '/')
    path[my_strlen(shell->home)] = '/';
  path[my_strlen(shell->home) + 1] = 0;
  path = my_strcat(path, ALIAS_FILE);
  if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC,
		 0644)) == -1)
    return ;
  head = shell->alias;
  while (head != NULL)
    {
      write_alias(head, fd);
      head = head->next;
    }
  free(path);
  close(fd);
}

void		set_alias(t_shell *shell, char *path)
{
  t_alias	*alias;
  int		i;
  int		obj;

  if ((alias = malloc(sizeof(t_alias))) == NULL)
    return ;
  i = -1;
  obj = my_strlen_spe(path + 6, '=');
  if ((alias->alias = malloc(obj + 1)) == NULL)
    return ;
  while (++i < obj)
    alias->alias[i] = (path + 6)[i];
  alias->alias[i] = 0;
  i = obj + 7;
  obj = my_strlen_spe(path + i + 1, '\'');
  if ((alias->command = malloc(obj + 1)) == NULL)
    return ;
  obj = i;
  i = -1;
  while ((path + obj + 1)[++i] != '\'')
    alias->command[i] = (path + obj + 1)[i];
  alias->command[i] = 0;
  alias->next = shell->alias;
  shell->alias = alias;
}

void	init_aliases(t_shell *shell)
{
  int	fd;
  char	*path;

  shell->alias = NULL;
  if ((shell->home == NULL) || (path = malloc(512)) == NULL)
    return ;
  path[0] = 0;
  path = my_strcat(path, shell->home);
  if (shell->home[my_strlen(shell->home)] != '/')
    path[my_strlen(shell->home)] = '/';
  path[my_strlen(shell->home) + 1] = 0;
  path = my_strcat(path, ALIAS_FILE);
  if ((fd = open(path, O_RDONLY)) == -1)
    return ;
  free(path);
  while ((path = get_next_line(fd)) != NULL)
    {
      if (is_valid_alias(path))
        set_alias(shell, path);
      free(path);
    }
  close(fd);
}
