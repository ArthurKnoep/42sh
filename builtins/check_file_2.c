/*
** check_file_2.c for check_file_2 in /home/arthur/delivery/PSU/PSU_2016_minishell1
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Fri Jan 20 14:33:24 2017 Arthur Knoepflin
** Last update Sat Mar 25 21:18:15 2017 Arthur Knoepflin
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int		is_folder(char *path)
{
  struct stat	stati;

  if ((stat(path, &stati)) == -1)
    return (0);
  else if (S_ISDIR(stati.st_mode))
    return (1);
  return (0);
}
