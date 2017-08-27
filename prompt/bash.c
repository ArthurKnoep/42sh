/*
** bash.c for bash in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May  4 23:38:58 2017 Arthur Knoepflin
** Last update Thu May 18 02:03:08 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include "my.h"

void	bash_prompt(t_shell *shell)
{
  char	*login;
  char	*hostname;

  if ((login = getenv("LOGNAME")) && (hostname = get_hostname()))
    {
      my_printf("\033[32;1m%s@%s\033[0m", login, hostname);
      free(hostname);
    }
  my_putstr(":");
  if (shell->current)
    my_printf("\033[34;1m%s\033[0m", shell->current);
  else
    my_printf("\033[34;1m?\033[0m");
  my_putstr(getuid() ? "$ " : "# ");
}
