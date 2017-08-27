/*
** cd.c for cd in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May 16 01:44:21 2017 Arthur Knoepflin
** Last update Sun May 21 03:49:25 2017 Nicolas Polomack
*/

#include "shell.h"

int	cd_b(t_shell *shell, int args)
{
  char	*str;
  int	i;

  i = move_dir(shell->cur->av, args, shell);
  if ((str = get_alias_cmd(shell, "cwdcmd")))
    quick_exec(shell, str);
  return (i);
}
