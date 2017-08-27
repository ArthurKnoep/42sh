/*
** tcsh.c for tcsh in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May  5 00:18:47 2017 Arthur Knoepflin
** Last update Fri May 12 13:49:41 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "shell.h"
#include "my.h"

void	tcsh_prompt(t_shell *shell)
{
  char	*hostname;

  if ((hostname = get_hostname()))
    my_printf("\e[4m%s\e[0m", hostname);
  free(hostname);
  my_putstr(":");
  if (shell->current)
    my_printf("\e[1m%s\e[0m", shell->current);
  else
    my_printf("\e[1m?\e[0m");
  my_putstr("> ");
}
