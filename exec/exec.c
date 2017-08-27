/*
** exec.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 11:14:09 2017 Nicolas Polomack
** Last update Sun May 21 20:18:18 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

void	exec_child(t_shell *shell, int i)
{
  if (!is_path(shell->cur->av[0]))
    execve(cat_path(shell->path, shell->cur->av[0], i), shell->cur->av,
	   environ);
  else
    execve(shell->cur->av[0], shell->cur->av, environ);
  if (errno == ENOEXEC)
    exit(my_print_err(shell->cur->av[0]) +
         my_print_err(": Exec format error. Binary \
file not executable.\n") - 1);
  exit(my_print_err(shell->cur->av[0]) +
       my_print_err(": Command not found.\n") - 1);
  exit(0);
}

int		check_access(char **final, t_shell *shell)
{
  int		i;
  int		ret;
  struct stat	stats;

  i = -1;
  if (is_path(final[0]))
    {
      if (stat(final[0], &stats) == 0)
	return (compare_stats(&stats));
    }
  else
    while (shell->path != NULL &&
	   shell->path[++i] != NULL)
      if (stat(cat_path(shell->path, final[0], i), &stats) == 0)
	{
	  ret = compare_stats(&stats);
	  return ((ret == 0) ? i : -2);
	}
  return (-1);
}

unsigned int	exec_action(t_shell *shell, unsigned int args)
{
  unsigned int	r;
  int		i;

  (void)args;
  r = exec_pipeline(shell);
  i = -1;
  if (shell->is_done)
    {
      free_shell(shell);
      exit(r);
    }
  while (shell->final[++i])
    free(shell->final[i]);
  free(shell->final);
  free_commands(shell);
  free(shell->line);
  if (shell->exit_str)
    free(shell->exit_str);
  if ((shell->exit_str = my_unsigned_to_char(r)) == NULL)
    exit(84);
  return (r);
}

unsigned int	exec_line(t_shell *shell, unsigned int args)
{
  if (parse_history(shell, args) == -1 || parse_alias(shell) == -1 ||
      parse_vars(shell) == -1 || magic(shell) == -1 ||
      (shell->line = my_epurcommand(shell->line)) == NULL ||
      parse_stars(shell) == 1 ||
      (shell->line = my_epurstr(shell->line)) == NULL)
    return (set_error(shell, 1));
  if (is_line_empty(shell->line))
    return (0);
  replace_home(shell);
  free(shell->last);
  shell->last = NULL;
  if ((shell->final = bufferize(shell->line,
				args = count_args(shell->line))) == NULL)
    return (1);
  if (set_commands(shell) == -1 || set_redirects(shell) == -1 ||
      check_error(shell) == -1)
    return (shell->exit = 1);
  shell->cur = shell->commands;
  args = exec_action(shell, args);
  return (args);
}
