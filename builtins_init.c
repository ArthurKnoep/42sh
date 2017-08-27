/*
** builtins_init.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri May 19 23:46:46 2017 Nicolas Polomack
** Last update Fri May 19 23:55:51 2017 Nicolas Polomack
*/

#include "shell.h"

int	nb_built(const char **str)
{
  int	i;

  i = 0;
  while (str[i])
    i += 1;
  return (i);
}
