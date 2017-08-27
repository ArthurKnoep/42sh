/*
** unalias.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun May  7 22:13:48 2017 Nicolas Polomack
** Last update Sun May  7 22:23:13 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"

void		remove_alias(t_shell *shell, char *alias)
{
  t_alias	*head;
  t_alias	*last;

  head = shell->alias;
  last = NULL;
  while (head)
    {
      if (strcmp(head->alias, alias) == 0)
	{
	  if (last)
	    last->next = head->next;
	  else
	    shell->alias = head->next;
	  free(head->alias);
	  free(head->command);
	  free(head);
	  return ;
	}
      last = head;
      head = head->next;
    }
}

int	unalias(t_shell *shell, char **aliases)
{
  int	i;

  i = -1;
  if (shell->alias == NULL)
    return (0);
  while (aliases[++i])
    remove_alias(shell, aliases[i]);
  return (0);
}
