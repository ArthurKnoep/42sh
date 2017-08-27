/*
** exec2.c for minishell1 in /home/nicolaspolomack/shell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Thu Jan 19 12:54:48 2017 Nicolas Polomack
** Last update Sat May 20 03:31:30 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "my.h"
#include "get_next_line.h"
#include "shell.h"

int	compare_stats(struct stat *stats)
{
  if (stats->st_mode & S_IXUSR)
    if (!S_ISDIR(stats->st_mode))
      return (0);
    else
      return (-3);
  else
    return (-2);
}

unsigned int	exec_redirected_builtins(t_shell *shell, int count,
					 int *i, int fds[2])
{
  int		fd;
  int		last;
  t_command	*head;
  unsigned int	ret;

  head = shell->cur;
  if (indexof_builtin(head->av[0]) == -1)
    return (0);
  fd = 0;
  if (head->r_type)
    {
      last = dup(1);
      fd = setup_right_redirect(head, fds, (head->r_type[1] == 0));
    }
  ret = exec_builtins(shell, count, i);
  if (fd)
    {
      close(fd);
      dup2(last, 1);
      close(last);
    }
  return (ret);
}

void		quick_exec(t_shell *shell, char *str)
{
  char		*save;
  char		**final;
  t_command	*cmds;

  if (is_line_empty(str))
    return ;
  save = shell->line;
  final = shell->final;
  cmds = shell->commands;
  shell->commands = NULL;
  shell->final = NULL;
  shell->line = str;
  exec_line(shell, 0);
  shell->line = save;
  shell->final = final;
  shell->commands = cmds;
}
