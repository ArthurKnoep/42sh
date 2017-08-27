/*
** print.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 11:08:11 2017 Nicolas Polomack
** Last update Sat May  6 22:17:55 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

int	my_print_err(char *err)
{
  write(2, err, my_strlen(err));
  return (1);
}

void	my_print_fd(char *str, int fd)
{
  write(fd, str, my_strlen(str));
}

int	my_print_ret(char *err, int ret)
{
  write(2, err, my_strlen(err));
  return (ret);
}

int	ret_error(t_shell *shell, char *message)
{
  shell->exit = 1;
  free(shell->exit_str);
  shell->exit_str = my_unsigned_to_char(1);
  my_printf(message);
  return (-1);
}
