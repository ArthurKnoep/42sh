/*
** config.c for config in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May 16 01:48:31 2017 Arthur Knoepflin
** Last update Tue May 16 01:53:37 2017 Arthur Knoepflin
*/

#include "shell.h"

int	config_b(t_shell *shell, int args)
{
  (void) args;
  return (launch_config(shell));
}
