/*
** mysh.c for 42sh in /home/nicolaspolomack/psu/PSU_2016_42sh/prompt
**
** Made by nicolaspolomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Jul 24 01:07:30 2017 nicolaspolomack
** Last update Tue Jul 24 01:21:38 2017 nicolaspolomack
*/

#include <stdlib.h>
#include "shell.h"
#include "my.h"

void mysh(t_shell *shell)
{
  if (shell->exit_str)
    my_printf("\e[1m\e[31m(%s)\e[0m ", shell->exit_str);
  my_putstr("\e[1m\e[31m42sh\e[21m\e[0m \e[92m");
  if (shell->current != NULL)
    my_putstr(shell->current);
  my_putstr("\e[0m ");
  my_putstr(getuid() ? "$" : "#");
  my_putstr("> ");
}