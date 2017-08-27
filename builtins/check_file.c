/*
** check_file.c for check_file in /home/arthur/delivery/PSU/PSU_2016_minishell1
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Mon Jan 16 20:43:46 2017 Arthur Knoepflin
** Last update Thu May 18 22:52:39 2017 Arthur Knoepflin
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

int		check_file_exist(char *path)
{
  struct stat	stati;

  if ((stat(path, &stati)) == -1)
    return (0);
  return (1);
}

int		check_file_access(char *path)
{
  struct stat	stati;

  if ((stat(path, &stati)) == -1)
    return (0);
  if ((stati.st_mode & S_IXUSR))
    return (1);
  else
    return (0);
  return (0);
}

int	print_error(char *cmd)
{
  if (!check_file_exist(cmd))
    {
      my_puterror(my_strcat(cmd, ": Command not found.\n"));
      return (0);
    }
  else if (!check_file_access(cmd))
    {
      my_puterror(my_strcat(cmd, ": Permission denied.\n"));
      return (0);
    }
  else if (is_folder(cmd))
    {
      my_puterror(my_strcat(cmd, ": Permission denied.\n"));
      return (0);
    }
  return (1);
}

int	print_error_path(char *cmd)
{
  if (check_file_exist(cmd) && (!check_file_access(cmd) ||
				is_folder(cmd)))
    {
      my_puterror(my_strcat(cmd, ": Permission denied.\n"));
      return (1);
    }
  return (0);
}

int		check_access_env(char *cmd)
{
  struct stat	stati;

  if (stat(cmd, &stati) == -1)
    my_puterror(my_strcat(cmd, ": No such file or directory.\n"));
  else if (!S_ISDIR(stati.st_mode))
    my_puterror(my_strcat(cmd, ": Not a directory.\n"));
  else if (access(cmd, X_OK) == -1)
    my_puterror(my_strcat(cmd, ": Permission denied.\n"));
  else
    return (1);
  if (!isatty(0))
    exit(1);
  else
    return (1);
}
