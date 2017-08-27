/*
** oh_my_zsh.c for oh_my_zsh in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May 12 18:42:45 2017 Arthur Knoepflin
** Last update Sun May 21 11:44:10 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <libgen.h>
#include "shell.h"
#include "my.h"

void	oh_my_zsh(t_shell *shell)
{
  char	*git;

  if (shell->exit == 0)
    my_putstr("\033[32;1m");
  else
    my_putstr("\033[31;1m");
  my_putstr("→  ");
  my_putstr("\033[0m");
  my_printf("\033[36;1m%s\033[0m ", basename(shell->current));
  git = show_cur_branch();
  if (git)
    {
      my_printf("\033[34;1mgit:(\033[0m\033[31;1m\
%s\033[0m\033[34;1m)\033[0m ", git);
      free(git);
    }
}
