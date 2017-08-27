/*
** token.c for 42sh in /home/benjamin/Dropbox/PSU_2016_42sh/parser_ll/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Wed May  3 13:48:30 2017 Benjamin
** Last update Sun May 21 14:33:16 2017 Benjamin
*/

#include <stdlib.h>
#include "parser_ll.h"
#include "bs.h"

static t_token	*set_token(t_token *token, t_grammar *gram,
			   char **tab, int *i)
{
  t_token	*tmp;
  t_token	*new;

  if (!(new = malloc(sizeof(t_token))))
    return (NULL);
  my_memset(new, 0, sizeof(t_token));
  token = token ? token : new;
  tmp = token;
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = (tmp == new) ? 0 : new;
  new->prev = (tmp == new) ? 0 : tmp;
  if (check_op_high(&new, gram, tab, i))
    return (token);
  else if (check_op_low(&new, gram, tab, i))
    return (token);
  else if (check_redir(&new, gram, tab, i))
    return (token);
  else
    {
      set_arg(&new, gram, tab, i);
      (*i)--;
    }
  return (token);
}

t_token		*fill_token(t_token *token, char *str)
{
  char		**tab;
  t_grammar	gram;
  int		i;

  i = -1;
  gram.op_high = bs_str_to_wordtab(OP_HIGH, " ");
  gram.op_low = bs_str_to_wordtab(OP_LOW, " ");
  gram.redir = bs_str_to_wordtab(REDIR, " ");
  tab = bs_str_to_wordtab(str, " ");
  while (tab[++i])
    token = set_token(token, &gram, tab, &i);
		my_free_tab(gram.op_high);
		my_free_tab(gram.op_low);
		my_free_tab(gram.redir);
		my_free_tab(tab);
  return (token);
}
