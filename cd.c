/*
** cd.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 11:06:20 2017 Nicolas Polomack
** Last update Sun May 21 03:58:03 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

int		check_dir(char *path)
{
  struct stat	stats;

  if (stat(path, &stats) == -1)
    return (-1);
  if (!S_ISDIR(stats.st_mode))
    return (-2);
  return (0);
}

int	move_dir2(char **final, int ac, t_shell *shell)
{
  char	*temp;
  int	check;

  if (ac == 2 && my_strcmp(final[1], "-") == 0)
    {
      if (shell->prev == NULL)
        return (my_print_err(": No such file or directory.\n"));
      temp = my_strdup(shell->prev);
      shell->prev = getcwd(NULL, 512);
      if (chdir(temp) == -1)
        return (my_print_err(temp) +
                my_print_err(": No such file or directory.\n") - 1);
      free(temp);
    }
  else
    if ((check = check_dir((ac == 2) ? final[1] : final[2])) == 0)
      {
	shell->prev = getcwd(NULL, 256);
	chdir((ac == 2) ? final[1] : final[2]);
      }
    else
      return (my_print_err((ac == 2) ? final[1] : final[2]) +
	      my_print_err((check == -2) ? ": Not a directory.\n" :
			   ": No such file or directory.\n") - 1);
  return (0);
}

int	move_dir(char **final, int ac, t_shell *shell)
{
  if (ac > 3 || (ac == 3 && my_strcmp(final[1], "--")))
    {
      my_print_err("cd: Too many arguments.\n");
      return (1);
    }
  else if (ac == 1 || (ac == 2 && !my_strcmp(final[1], "--")))
    {
      shell->prev = getcwd(NULL, 512);
      if (shell->home == NULL)
        return (my_print_err("cd: No home directory.\n"));
      else if (chdir(shell->home) == -1)
        return (my_print_err("cd: Can't change to home directory.\n"));
      shell->current = get_current(shell->current, shell->home);
      return (0);
    }
  else
    if (move_dir2(final, ac, shell))
      return (1);
  shell->current = get_current(shell->current, shell->home);
  return (0);
}
