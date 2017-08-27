/*
** op_high.c for 42.c in /home/benjamin/Dropbox/PSU_2016_42sh/parser_ll/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Fri May  5 14:51:23 2017 Benjamin
** Last update Thu May 11 13:37:15 2017 Benjamin
*/

#include "bs.h"
#include "parser_ll.h"

int	check_op_high(t_token **new, t_grammar *gram,
		       char **tab, int *i)
{
  int	j;

  j = -1;
  while (gram->op_high[++j])
    {
      if (!my_strcmp(gram->op_high[j], tab[*i]))
	{
	  (*new)->type = my_strdup("OP_HIGH");
	  (*new)->value = my_strdup(tab[*i]);
	  return (1);
	}
    }
  return (0);
}
