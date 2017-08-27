/*
** misc.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Apr 18 18:57:06 2017 Nicolas Polomack
** Last update Tue Apr 18 19:02:20 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	get_input()
{
  char	c;

  c = -1;
  read(0, &c, 1);
  return (c);
}

void	handle_error(char *msg)
{
  perror(msg);
  exit(84);
}
