/*
** op_low.c for 42.c in /home/benjamin/Dropbox/PSU_2016_42sh/parser_ll/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Fri May  5 14:51:23 2017 Benjamin
** Last update Thu May 11 13:48:20 2017 Benjamin
*/

#include "bs.h"
#include "parser_ll.h"

int	check_op_low(t_token **new, t_grammar *gram,
		       char **tab, int *i)
{
  int	j;

  j = -1;
  while (gram->op_low[++j])
    {
      if (!my_strcmp(gram->op_low[j], tab[*i]))
	{
	  (*new)->type = my_strdup("OP_LOW");
	  (*new)->value = my_strdup(tab[*i]);
	  return (1);
	}
    }
  return (0);
}
