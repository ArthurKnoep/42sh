/*
** bufferize.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Jan  9 10:55:14 2017 Nicolas Polomack
** Last update Sun May 21 11:49:53 2017 Arthur Knoepflin
*/

#include <sys/stat.h>
#include "my.h"

int	is_right_redirect(char *str)
{
  return (my_strcmp(str, ">") == 0 || my_strcmp(str, ">>") == 0);
}

int	is_left_redirect(char *str)
{
  return (my_strcmp(str, "<") == 0 || my_strcmp(str, "<<") == 0);
}

int	is_to_fork(char c)
{
  return (c == ';' || c == 'e' || c == 'o');
}
