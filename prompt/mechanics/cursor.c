/*
** cursor.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat Apr 22 17:04:32 2017 Nicolas Polomack
** Last update Tue May 23 16:33:10 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "my.h"

void	buffer_seq(t_shell *shell, char **str, int *dir, char c)
{
  *str = NULL;
  *dir = -1;
  insert_char_cur(str, c, 0);
  if (!shell->w.left || !shell->w.right || !shell->w.upw ||
      !shell->w.downw || !shell->w.home || !shell->w.end)
    return ;
  while (*dir == -1 && (strstr(shell->w.left, *str) ||
			strstr(shell->w.right, *str) ||
			strstr(shell->w.upw, *str) ||
			strstr(shell->w.downw, *str) ||
			strstr(shell->w.home, *str) ||
			strstr(shell->w.end, *str)))
    {
      while (!(c = get_input()));
      insert_char_cur(str, c, strlen(*str));
      if (!strcmp(*str, shell->w.left))
	*dir = 1;
      else if (!strcmp(*str, shell->w.right))
	*dir = 2;
      else if (!strcmp(*str, shell->w.upw))
	*dir = 3;
      else if (!strcmp(*str, shell->w.downw))
	*dir = 4;
      else if (!strcmp(*str, shell->w.home))
	*dir = 5;
      else if (!strcmp(*str, shell->w.end))
	*dir = 6;
    }
}

void	move_forw(t_shell *shell)
{
  if (shell->line &&
      shell->w.cur < ((int)strlen(shell->line)))
    {
      shell->w.cur += 1;
      write(1, shell->w.forw, strlen(shell->w.forw));
    }
}

void	move_backw(t_shell *shell)
{
  if (shell->w.cur)
    {
      shell->w.cur -= 1;
      write(1, shell->w.backw, strlen(shell->w.backw));
    }
}

void	move_upw(t_shell *shell)
{
  if (shell->hist.last == NULL)
    return ;
  suppress_line(shell);
  if (shell->hist.cur == NULL)
    {
      free(shell->hist.cur_line);
      if (shell->line)
	shell->hist.cur_line = strdup(shell->line);
      else
	shell->hist.cur_line = NULL;
      shell->hist.cur = shell->hist.last;
    }
  else if (shell->hist.cur->prev)
    shell->hist.cur = shell->hist.cur->prev;
  free(shell->line);
  shell->line = construct_alias(shell->hist.cur->cmd);
  if (shell->line)
    {
      my_putstr(shell->line);
      shell->w.cur = strlen(shell->line);
    }
}

void	move_downw(t_shell *shell)
{
  if (shell->hist.last == NULL ||
      shell->hist.cur == NULL)
    return ;
  suppress_line(shell);
  if (shell->hist.cur && !shell->hist.cur->next)
    return (set_hist_line(shell));
  else if (shell->hist.cur && shell->hist.cur->next)
    shell->hist.cur = shell->hist.cur->next;
  free(shell->line);
  shell->line = construct_alias(shell->hist.cur->cmd);
  my_putstr(shell->line);
  shell->w.cur = strlen(shell->line);
}
