/*
** parse.c for 42sh in /home/benjamin/Dropbox/PSU_2016_42sh/parser_ll
**
** Made by
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Tue May  2 16:54:18 2017
** Last update Tue May  2 16:59:03 2017 Benjamin
*/

#include <stdlib.h>
#include "parser_ll.h"
#include "bs.h"

static void	free_token(t_token **token)
{
  t_token	*tmp;

  while ((*token)->next)
    {
      tmp = (*token);
      (*token) = (*token)->next;
      free(tmp->type);
      free(tmp->value);
      free(tmp);
    }
  free((*token)->type);
  free((*token)->value);
  free(*token);
}

t_ast		*parser_ll(char *str)
{
  t_ast		*ast;
  t_token	*token;

  if (!str)
    return (NULL);
  token = NULL;
  ast = NULL;
  token = fill_token(token, str);
  ast = create_ast(ast, token);
  while (ast->father)
    ast = ast->father;
  while (token && token->prev)
    token = token->prev;
  if (token)
    free_token(&token);
  print_ast(ast);
  return (ast);
}
