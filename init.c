/*
** init.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Apr 18 18:57:40 2017 Nicolas Polomack
** Last update Sun May 21 04:35:26 2017 Nicolas Polomack
*/

#include <curses.h>
#include <term.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "shell.h"

void		set_raw(struct termio *oterm)
{
  struct termio	nterm;

  nterm = *oterm;
  nterm.c_lflag &= ~(ICANON | ECHO);
  nterm.c_cc[VTIME] = 0;
  nterm.c_cc[VMIN] = 0;
  if (ioctl(0, TCSETA, &nterm) == -1)
    handle_error("ioctl");
}

int	init_shell(t_shell *shell)
{
  srand(getpid() * time(NULL));
  shell->exit = 0;
  shell->path = init_path(getenv("PATH"));
  shell->home = getenv("HOME");
  if ((shell->current = malloc(512)) == NULL)
    handle_error("malloc");
  shell->current[0] = 0;
  shell->current = get_current(shell->current, shell->home);
  shell->exit = 0;
  shell->is_comp = 0;
  shell->last = NULL;
  shell->prev = NULL;
  shell->exit_str = NULL;
  shell->fds = NULL;
  shell->is_done = 0;
  init_history(shell);
  init_aliases(shell);
  parse_rc(shell);
  init_vars(shell);
  shell->path = (shell->path) ? shell->path : set_default_path();
  get_prompt(shell);
  init(shell);
  return (0);
}

void	init(t_shell *shell)
{
  shell->tty = isatty(0);
  if (shell->tty)
    {
      if (getenv("TERM") == NULL ||
	  setupterm(NULL, 0, NULL) == ERR)
	{
	  shell->ioctl = 0;
	  return ;
	}
      shell->ioctl = ioctl(0, TCGETA, &shell->w.oterm) + 1;
      shell->w.smkx = tigetstr("smkx");
      shell->w.clear = tigetstr("clear");
      shell->w.end = tigetstr("kend");
      shell->w.home = tigetstr("khome");
      shell->w.forw = tigetstr("cuf1");
      shell->w.backw = tigetstr("cub1");
      shell->w.upw = tigetstr("kcuu1");
      shell->w.downw = tigetstr("kcud1");
      shell->w.left = tigetstr("kcub1");
      shell->w.right = tigetstr("kcuf1");
      shell->line = NULL;
    }
}

void	init_prompt(t_shell *shell)
{
  shell->hist.cur = NULL;
  shell->hist.cur_line = NULL;
  if (shell->tty)
    {
      if (shell->ioctl)
	{
	  printf("%s", shell->w.smkx);
	  fflush(stdout);
	}
      get_prompt(shell);
      sauv_prompt(shell);
      print_prompt(shell);
    }
}
