/*
** unsetenv.c for unsetenv in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 17 09:47:37 2017 Arthur Knoepflin
** Last update Wed May 17 09:51:08 2017 Arthur Knoepflin
*/

#include "shell.h"
#include "my.h"

int	unsetenv_b(t_shell *shell, int args)
{
  int	r;

  r = 0;
  if (args == 1 && my_strcmp(shell->cur->av[0], "unsetenv") == 0)
    r = my_print_err("unsetenv: Too few arguments.\n");
  else if (my_strcmp(shell->cur->av[0], "unsetenv") == 0)
    r = unset_env(shell->cur->av);
  else
    r = my_print_err(shell->cur->av[0]) +
      my_print_err(": Too many arguments.\n") - 1;
  reload_shell(shell);
  return (r);
}
