/*
** alias2.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:42:33 2017 Nicolas Polomack
** Last update Tue Jun 20 19:36:14 2017 nicolaspolomack
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"
#include "my.h"

int		add_alias(t_shell *shell, char *alias,
			  char *command)
{
  t_alias	*elem;

  elem = shell->alias;
  while (elem != NULL)
    {
      if (my_strcmp(elem->alias, alias) == 0)
        {
          free(elem->command);
          elem->command = my_strdup(command);
          return (0);
        }
      elem = elem->next;
    }
  if ((elem = malloc(sizeof(t_alias))) == NULL)
    handle_error("malloc");
  elem->alias = strdup(alias);
  elem->command = strdup(command);
  if (elem->alias == NULL || elem->command == NULL)
    handle_error("malloc");
  elem->next = shell->alias;
  shell->alias = elem;
  return (0);
}

int		disp_all_alias(t_shell *shell)
{
  t_alias	*head;
  int		mode;
  int		i;

  if (shell->alias == NULL)
    return (0);
  head = shell->alias;
  while (head != NULL)
    {
      mode = 0;
      i = -1;
      while (head->command[++i])
	if (head->command[i] == ' ')
	  mode = 1;
      my_printf(mode ? "alias %s='%s'\n" : "alias %s=%s\n",
		head->alias, head->command);
      head = head->next;
    }
  return (0);
}

int		disp_alias(t_shell *shell, char *alias)
{
  t_alias	*head;

  if (shell->alias == NULL)
    return (0);
  head = shell->alias;
  while (head != NULL)
    {
      if (my_strcmp(head->alias, alias) == 0)
        printf("alias %s='%s'\n", head->alias, head->command);
      head = head->next;
    }
  return (0);
}

char	*construct_alias(char **tab)
{
  int	i;
  int	len;
  char	*ret;

  len = 0;
  i = -1;
  while (tab[++i])
    len += ((!!i) + strlen(tab[i]));
  if ((ret = malloc(len + 1)) == NULL)
    handle_error("malloc");
  *ret = 0;
  i = -1;
  while (tab[++i])
    strcat(i ? strcat(ret, " ") : ret, tab[i]);
  return (ret);
}

char		*get_alias_cmd(t_shell *shell, char *name)
{
  t_alias	*head;

  if (name == NULL)
    return (NULL);
  head = shell->alias;
  while (head)
    {
      if (!strcmp(head->alias, name))
	return (strdup(head->command));
      head = head->next;
    }
  return (NULL);
}
