/*
** arg.c for 42.c in /home/benjamin/Dropbox/PSU_2016_42sh/parser_ll/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Fri May  5 14:51:23 2017 Benjamin
** Last update Thu May 11 13:15:05 2017 Benjamin
*/

#include "bs.h"
#include "parser_ll.h"

static int	check_is_arg(t_grammar *gram, char **tab, int *i)
{
  int		j;
  int		count;

  j = -1 + (count = 0);
  while (gram->op_high[++j])
    {
      if (!my_strcmp(gram->op_high[j], tab[*i]))
	count++;
    }
  j = -1;
  while (gram->op_low[++j])
    {
      if (!my_strcmp(gram->op_low[j], tab[*i]))
	count++;
    }
  j = -1;
  while (gram->redir[++j])
    {
      if (!my_strcmp(gram->redir[j], tab[*i]))
	count++;
    }
  if (count == 0)
    return (1);
  return (0);
}

int	set_arg(t_token **new, t_grammar *gram,
		char **tab, int *i)
{
  if (!check_is_arg(gram, tab, i))
    (*i)++;
  while (tab[*i] && check_is_arg(gram, tab, i))
    {
      (*new)->type = my_strdup("ARG");
      if ((*new)->value)
	{
	  (*new)->value = bs_strcat((*new)->value, " ");
	  (*new)->value = bs_strcat((*new)->value, tab[*i]);
	}
      else
	(*new)->value = my_strdup(tab[*i]);
      (*i)++;
    }
  return (0);
}
