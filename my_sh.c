/*
** my_exec.c for my_exec in /home/nicolaspolomack/shell/bs_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Jan  3 09:03:30 2017 Nicolas Polomack
** Last update	Sat May 13 21:02:27 2017 Full Name
*/

#include <string.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <curses.h>
#include "my.h"
#include "get_next_line.h"
#include "parser_ll.h"
#include "shell.h"

void	diagnose_status(unsigned int status)
{
  if ((status % 128) == SIGSEGV)
    my_print_err("Segmentation fault");
  else if ((status % 128) == SIGFPE)
    my_print_err("Floating exception");
  else if ((status % 128) == SIGBUS)
    my_print_err("Bus error");
  else if ((status % 128) == SIGABRT)
    my_print_err("Aborted");
  else if ((status % 128) == SIGILL)
    my_print_err("Illegal instruction");
  else if ((status % 128) == SIGKILL)
    my_print_err("Killed");
  else if ((status % 128) == SIGTERM)
    my_print_err("Terminated");
  else if ((status % 128) == SIGPIPE)
    return ;
  my_print_err((WCOREDUMP(status)) ? " (core dumped)\n" : "\n");
}

void		reload_shell(t_shell *shell)
{
  int		k;
  char		*path;

  if ((path = getenv("PATH")))
    {
      if (shell->path)
	{
	  k = -1;
	  while (shell->path[++k])
	    free(shell->path[k]);
	  free(shell->path);
	}
      shell->path = init_path(path);
    }
  shell->home = getenv("HOME");
  shell->current = get_current(shell->current, shell->home);
}

void	execute(t_shell *shell)
{
  char	*str;

  if (shell->ioctl)
    prompt_line(shell);
  else
    shell->line = get_next_line(0);
  if (shell->line && shell->tty && shell->ioctl)
    write(1, "\n", 1);
  if (!shell->line)
    shell->line = strdup("exit");
  clear_comment(shell);
  if (!is_line_empty(shell->line))
    {
      if ((str = get_alias_cmd(shell, "postcmd")))
	quick_exec(shell, str);
      shell->exit = exec_line(shell, shell->tty);
      if ((str = get_alias_cmd(shell, "precmd")))
	quick_exec(shell, str);
    }
}

static int	start_standard_shell(t_shell *shell)
{
  signal(SIGINT, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
  while (1)
    {
      shell->line = NULL;
      shell->w.cur = 0;
      init_prompt(shell);
      execute(shell);
    }
  if (shell->tty)
    {
      write(1, "exit\n", 5);
      if (shell->ioctl)
	{
	  ioctl(0, TCSETA, &shell->w.oterm);
	  my_putstr(tigetstr("rmkx"));
	  fflush(stdout);
	}
    }
  return (shell->exit);
}

int		main(int ac, char **av)
{
  t_shell	shell;
  int		fd;

  setenv("SHELL", av[0], 1);
  if (init_shell(&shell) == -1)
    return (84);
  shell.av = av + ((ac == 1) ? 0 : 1);
  if (ac == 1)
    return (start_standard_shell(&shell));
  else
    {
      if ((fd = open(av[1], O_RDONLY)) == -1)
	{
	  my_puterror(av[1]);
	  my_puterror(": No such file or directory\n");
	  return (1);
	}
      if (dup2(fd, 0) == -1)
	return (1);
      shell.tty = 0;
      shell.ioctl = 0;
      return (start_standard_shell(&shell));
    }
  return (0);
}
