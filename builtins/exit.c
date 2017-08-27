/*
** exit.c for exit in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon May 15 13:53:15 2017 Arthur Knoepflin
** Last update Mon May 15 13:55:01 2017 Arthur Knoepflin
*/

#include "shell.h"

int	exit_b(t_shell *shell, int args)
{
  return (check_exit(shell, args));
}
