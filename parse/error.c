/*
** error.c for minishell2 in /home/nicolaspolomack/shell2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar 30 01:22:31 2017 Nicolas Polomack
** Last update Sun May 21 04:24:08 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "my.h"
#include "shell.h"

int		check_error(t_shell *shell)
{
  t_command	*head;

  head = shell->commands;
  while (head)
    {
      if (((head->av == NULL || head->av[0] == NULL) &&
	   head->next) ||
	  ((head->link == '|' || head->link == 'e' ||
	    head->link == 'o') && !head->next))
	{
	  shell->exit = 1;
	  free(shell->exit_str);
	  shell->exit_str = my_unsigned_to_char(0);
	  my_printf("Invalid null command.\n");
	  return (-1);
	}
      head = head->next;
    }
  return (0);
}
