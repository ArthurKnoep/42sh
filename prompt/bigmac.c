/*
** bigmac.c for bigmac in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May  5 10:10:32 2017 Arthur Knoepflin
** Last update Sun May  7 23:41:32 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"

void	bigmac_prompt(t_shell *shell)
{
  char	*login;
  char	*hostname;

  my_putstr("[");
  if ((login = getenv("LOGNAME")))
    my_printf("\033[35;1m%s\033[0m", login);
  my_putstr("@");
  if ((hostname = get_hostname()))
    my_printf("\033[31;1m%s\033[0m", hostname);
  free(hostname);
  my_putstr(" ");
  if (shell->current)
    my_printf("\033[32;1m%s\033[0m", shell->current);
  else
    my_printf("\033[32;1m?\033[0m");
  my_putstr(getuid() ? "]$ " : "]# ");
}
