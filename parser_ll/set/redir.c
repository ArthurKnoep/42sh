/*
** redir.c for 42.c in /home/benjamin/Dropbox/PSU_2016_42sh/parser_ll/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Fri May  5 14:51:23 2017 Benjamin
** Last update Wed May 10 11:36:55 2017 Benjamin
*/

#include "bs.h"
#include "parser_ll.h"

int	check_redir(t_token **new, t_grammar *gram,
		    char **tab, int *i)
{
  int	j;

  j = -1;
  while (gram->redir[++j])
    {
      if (!my_strcmp(gram->redir[j], tab[*i]))
	{
	  (*new)->type = my_strdup("REDIR");
	  (*new)->value = my_strdup(tab[*i]);
	  return (1);
	}
    }
  return (0);
}
