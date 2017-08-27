/*
** auto_list.c for auto_list in /home/Maxime/delivery/PSU/PSU_2016_42sh/auto_completation/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Tue May  9 20:54:46 2017 Maxime Jenny
** Last update	Sat May 20 19:33:37 2017 Full Name
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "auto_complete.h"
#include "my.h"

void		destroy_the_list(t_match **list)
{
  t_match	*prev;
  t_match	*temp;

  temp = *list;
  while (temp)
    {
      prev = temp;
      free(temp->cmd);
      temp = temp->next;
      free(prev);
    }
  *list = NULL;
}

void		show_autolist(t_shell *shell, t_match *list)
{
  t_match	*tmp;
  char		*str;
  char		*cmd;

  if (!list)
    return ;
  tmp = list;
  str = strdup("echo '");
  printf("\n");
  while (tmp)
    {
      if (strcmp(tmp->cmd, "..") && strcmp(tmp->cmd, "."))
	{
	    if (asprintf(&cmd, "%s%s\\n", str, tmp->cmd) == -1)
	      handle_error("malloc");
	  free(str);
	  str = cmd;
	}
      tmp = tmp->next;
    }
  if (asprintf(&cmd, "%s' | sort | column", str) == -1)
    handle_error("malloc");
  free(str);
  str = cmd;
  quick_exec(shell, cmd);
}

int		add_in_autolist(t_match **list, char *cmd)
{
  t_match	*tmp;
  t_match	*elem;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    return (-1);
  elem->cmd = cmd;
  elem->next = NULL;
  if (*list == NULL)
    {
      *list = elem;
      return (0);
    }
  tmp = *list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = elem;
  return (0);
}
