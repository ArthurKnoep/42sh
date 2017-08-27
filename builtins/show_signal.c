/*
** show_signal.c for show_signal in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May 18 22:43:50 2017 Arthur Knoepflin
** Last update Thu May 18 23:37:17 2017 Arthur Knoepflin
*/

#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

int	show_signal(int pid)
{
  int	ret;

  ret = 0;
  waitpid(pid, &ret, 0);
  if (!WIFEXITED(ret))
    diagnose_status(ret);
  return (WIFEXITED(ret) ? WEXITSTATUS(ret) : ret);
}
