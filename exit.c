/*
** exit.c for mysh in /home/nicolaspolomack/shell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Thu Jan 19 12:39:44 2017 Nicolas Polomack
** Last update Sun May 21 04:33:14 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "shell.h"
#include "my.h"

int	check_exit(t_shell *shell, int args)
{
  if (args > 2 || (args == 2 &&
		   (shell->cur->av[1][0] < '0' || shell->cur->av[1][0] > '9') &&
		   shell->cur->av[1][0] != '-'))
    my_print_err("exit: Expression Syntax.\n");
  else if (args == 2 && !my_str_isnum(shell->cur->av[1] + 1))
    my_print_err("exit: Badly Formed Number.\n");
  else
    {
      shell->is_done = 1;
      shell->exit = ((args == 2) ?
		     get_unsigned_int(shell->cur->av[1]) : shell->exit);
      return (shell->exit);
    }
  return (1);
}

int	set_error(t_shell *shell, int ret)
{
  shell->exit = ret;
  free(shell->exit_str);
  shell->exit_str = my_unsigned_to_char(ret);
  return (ret);
}
