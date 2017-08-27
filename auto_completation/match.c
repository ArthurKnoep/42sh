/*
** match.c for match in /home/arthur/delivery/CPool_match-nmatch/
**
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
**
** Started on  Sat Oct 15 18:43:19 2016 Arthur Knoepflin
** Last update	Sun May 21 11:44:05 2017 Full Name
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "auto_complete.h"
#include "shell.h"

int		for_bi(t_match **list, char *str, t_auto *t)
{
  char		**bi;
  int		i;
  char		*str2;

  bi = get_builtin_tab();
  i = 0;
  str2 = my_strcatdup(str, "*");
  if (t->pre_token[0] != 0)
    return (0);
  while (bi[i])
    {
      if (match(bi[i], str2) == 1)
	{
	  if ((add_in_autolist(list, strdup(bi[i]))) == -1)
      	    return (-1);
	}
      i++;
    }
  return (0);
}

int		filter(const struct dirent *l)
{
  if ((my_strcmp((char *)l->d_name, ".")) == 0 ||
      (my_strcmp((char *)l->d_name, "..")) == 0)
    return (0);
  return (1);
}

static char	*find_occurences(t_match **list)
{
  int		i;
  char		prec;
  int		g;
  char		*str;
  t_match	*tmp;

  g = 0;
  str = NULL;
  i = 0;
  while (g == 0)
    {
      tmp = *list;
      prec = tmp->cmd[i];
      while (tmp && tmp->cmd[i] == prec)
	tmp = tmp->next;
      if (tmp)
	{
	  str = strndup(tmp->cmd, i);
	  g = 1;
	}
      i++;
    }
  return (str);
}

void		transform(t_shell *shell, t_auto *t, t_match **list, char **s)
{
  char		*str;

  if ((*list)->next == NULL)
    {
      str = strdup((*list)->cmd);
      shell->is_comp = 0;
    }
  else
    str = find_occurences(list);
  *s ? free(shell->line) : 0;
  shell->line = my_strcatdup(t->pre_token, str);
  shell->line = my_fstrcat(shell->line, t->post_token, 1);
  str = delete_str(*s, str);
  if (t->post_token && (*list)->next == NULL)
    *s = my_strcatdup(str, t->post_token);
  shell->w.cur = my_strlen(shell->line);
  t->is_a_dir = 0;
}

int	match(char *s1, char *s2)
{
  int	ret;

  if (*s1 == '\0' && *s2 == '\0')
    return (1);
  else if (*s2 == '*' && *s1 == '\0')
    ret = match(s1, s2 + 1);
  else if (*s2 == '*')
    ret = (match(s1, s2 + 1) || match(s1 + 1, s2));
  else if (*s1 == *s2)
    ret = match(s1 + 1, s2 + 1);
  else
    return (0);
  return (ret);
}
