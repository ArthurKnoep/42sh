/*
** unalias.c for unalias in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May 16 02:16:22 2017 Arthur Knoepflin
** Last update Tue May 16 02:17:59 2017 Arthur Knoepflin
*/

#include "shell.h"

int	unalias_b(t_shell *shell, int args)
{
  if (args >= 2)
    return (unalias(shell, shell->cur->av + 1));
  else
    return (my_print_err("unalias: Too few arguments.\n"));
}
