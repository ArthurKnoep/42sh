/*
** exec_arg_2.c for exec_2 in /home/arthur/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <arthur@epitech.net>
** 
** Started on  Thu Jan 12 21:05:21 2017 
** Last update Thu May 18 22:34:50 2017 Arthur Knoepflin
*/

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

void	exec_not_path(char *cmd, char **arg, char **ae)
{
  if (print_error(cmd))
    if (execve(cmd, arg, ae) == -1)
      if (errno == ENOEXEC)
	my_puterror(my_strcat(cmd, ": Exec format error.\
 Binary file not executable.\n"));
}
