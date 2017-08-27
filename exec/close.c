/*
** close.c for minishell2 in /home/nicolaspolomack/psu/2/PSU_2016_minishell2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun Mar 26 19:40:16 2017 Nicolas Polomack
** Last update Sun Apr  2 22:14:52 2017 Nicolas Polomack
*/

#include <unistd.h>

int	close_pipes(int *pipes)
{
  int	i;

  i = -1;
  while (pipes[++i])
    close(pipes[i]);
  return (0);
}
