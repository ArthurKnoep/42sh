/*
** test.c for minishell1 in /home/nicolaspolomack/shell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Sat Jan 14 18:04:39 2017 Nicolas Polomack
** Last update Sun May 21 04:12:04 2017 Nicolas Polomack
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "get_next_line.h"
#include "shell.h"
#include "my.h"

int		exec_branch(t_shell *shell,
			    t_command **head,
			    int fds[3], int *ret)
{
  int	r;

  if ((is_to_fork((*head)->link) || (*head)->next == NULL) &&
      exec_redirected_builtins(shell, fds[2], &r, fds) != 0)
    {
      if (*ret != 0)
	close(*ret);
      skip_commands(head, r);
      if (*head)
	(*head) = (*head)->next;
      return (r);
    }
  if ((*head)->l_type)
    *ret = setup_left_redirect((*head)->l_name,
			       (*head)->l_type[1] == 0);
  if ((fds[2] = fork()) == -1)
    return (84);
  fds[2] ? (r = father_action(head, ret, fds, shell)) :
    exec_piped_child(*ret, *head, fds, shell);
  return (r);
}

int		exec_pipeline(t_shell *shell)
{
  int		fds[3];
  t_command	*head;
  int		ret;
  int		r;

  shell->fds = NULL;
  shell->pgid = 0;
  head = shell->commands;
  ret = 0;
  while (head)
    {
      shell->cur = head;
      fds[2] = -1;
      while (head->av[++(fds[2])]);
      if (head->link == '|')
	if (pipe(fds) == -1)
	  return (ret_error(shell, "Can't make pipe.\n"));
      if ((r = exec_branch(shell, &head, fds, &ret)) == 84)
	return (84);
    }
  return (r);
}

void	exec_piped_child(int ret,
			 t_command *head,
			 int *fds,
			 t_shell *shell)
{
  int	i;

  signal(SIGINT, SIG_DFL);
  set_fground(shell);
  setup_exec(head, fds, ret);
  ret = -1 + 0 * (i = 0);
  if (head->link == '|')
    {
      close(fds[0]);
      close(fds[1]);
    }
  while (head->av[++ret]);
  if (is_path(shell->cur->av[0]) || exec_builtins(shell, ret, &i) == 0)
    {
      if ((i = check_access(shell->cur->av, shell)) >= 0)
	exec_child(shell, i);
      else
	{
	  my_print_err(shell->cur->av[0]);
	  my_print_err((i == -1) ? ": Command not found.\n" :
		       ": Permission denied.\n");
	  i = 1;
	}
    }
  exit(i);
}

int	get_return(t_shell *shell)
{
  int	i;
  int	r;
  int	final;

  i = -1;
  final = 0;
  while (shell->fds[++i]);
  i -= 1;
  while (i >= 0)
    {
      waitpid(shell->fds[i], &r, 0);
      if (!WIFEXITED(r))
	diagnose_status(r);
      if (r && !final)
	final = r;
      i -= 1;
    }
  free(shell->fds);
  shell->fds = NULL;
  return (final);
}

int	father_action(t_command **head,
		      int *ret,
		      int *fds,
		      t_shell *shell)
{
  int	r;

  if (shell->pgid == 0)
    shell->pgid = fds[2];
  if (*ret != 0)
    close(*ret);
  if ((*head)->link == '|')
    {
      *ret = fds[0];
      close(fds[1]);
    }
  else
    *ret = 0;
  insert_int(&shell->fds, fds[2]);
  r = 0;
  if (!((*head)->next) || (*head)->link != '|')
    {
      r = get_return(shell);
      shell->pgid = 0 + (fds[2] = -1) * 0;
      tcsetpgrp(0, getpid());
    }
  skip_commands(head, WEXITSTATUS(r));
  if (*head)
    (*head) = (*head)->next;
  return (WIFEXITED(r) ? WEXITSTATUS(r) : r % 128 + 128);
}
