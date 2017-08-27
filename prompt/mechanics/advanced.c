/*
** advanced.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue May 16 18:37:16 2017 Nicolas Polomack
** Last update Wed May 17 16:02:51 2017 Nicolas Polomack
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "my.h"

void	move_end(t_shell *shell)
{
  int	len;

  len = strlen(shell->line);
  while (shell->w.cur < len)
    {
      write(1, shell->w.forw, strlen(shell->w.forw));
      shell->w.cur += 1;
    }
}

void	move_home(t_shell *shell)
{
  while (shell->w.cur > 0)
    {
      write(1, shell->w.backw, strlen(shell->w.backw));
      shell->w.cur -= 1;
    }
}

void	set_hist_line(t_shell *shell)
{
  free(shell->line);
  if (shell->hist.cur_line)
    shell->line = strdup(shell->hist.cur_line);
  else
    shell->line = NULL;
  if (shell->line)
    {
      my_putstr(shell->line);
      shell->w.cur = strlen(shell->line);
    }
  shell->hist.cur = NULL;
}

void	suppress_line(t_shell *shell)
{
  int	len;

  len = ((shell->line != NULL) ? strlen(shell->line) : 0);
  while (shell->w.cur < len)
    {
      shell->w.cur += 1;
      write(1, shell->w.forw, strlen(shell->w.forw));
    }
  while (shell->w.cur > 0)
    {
      shell->w.cur -= 1;
      write(1, shell->w.backw, strlen(shell->w.backw));
      write(1, " ", 1);
      write(1, shell->w.backw, strlen(shell->w.backw));
    }
}
