/*
** alias.c for alias in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon May 15 13:30:51 2017 Arthur Knoepflin
** Last update Sun May 21 03:48:57 2017 Nicolas Polomack
*/

#include "shell.h"

int	alias(t_shell *shell, int args)
{
  if (args == 1)
    return (disp_all_alias(shell));
  else if (args == 2)
    return (disp_alias(shell, shell->cur->av[1]));
  else if (args >= 3)
    return (add_alias(shell, shell->cur->av[1],
		      construct_alias(shell->cur->av + 2)));
  return (1);
}
