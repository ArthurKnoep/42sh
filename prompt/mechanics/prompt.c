/*
** prompt.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Apr 18 19:05:01 2017 Nicolas Polomack
** Last update	Sat May 13 21:03:36 2017 Full Name
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "auto_complete.h"

static void	block_read_zero(void)
{
  fd_set	rdfs;

  FD_ZERO(&rdfs);
  FD_SET(STDIN_FILENO, &rdfs);
  select(1, &rdfs, NULL, NULL, NULL);
}

static void	make_action(t_shell *shell, char c)
{
  if (c == 12)
    clear_term(shell);
  else if (c == 24)
    {
      block_read_zero();
      c = get_input();
      if (c == 5)
	tmp_file(shell);
      else if (c != -1)
	insert_char(&shell->line, c);
    }
  else if (c == 127)
    remove_char(shell);
  else if (shell->tty && c == '\t')
    auto_complete(shell, getenv("PATH"));
  else if (shell->tty && (c == shell->w.forw[0] ||
			  c == shell->w.backw[0]))
    move_cursor(shell, c);
  else
    add_char(shell, c);
}

void	prompt_line(t_shell *shell)
{
  char	c;

  if (shell->tty)
    set_raw(&shell->w.oterm);
  shell->hist.cur = NULL + (c = -1) * 0;
  while (c != 10)
    {
      block_read_zero();
      if ((c = get_input()) == -1)
	{
	  if (shell->tty)
	    continue ;
	  else
	    return ;
	}
      if (c == 10 && !shell->line)
        shell->line = strdup("");
      if (c == 10 || c == 0 || c == 4 ||
          (c == -2 && !shell->tty))
        break;
      make_action(shell, c);
    }
  if (shell->tty &&
      ioctl(0, TCSETA, &shell->w.oterm) == -1)
    handle_error("ioctl");
}
