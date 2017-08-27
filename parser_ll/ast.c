/*
** ast.c for 42sh in /home/benjamin/Dropbox/PSU_2016_42sh/parser_ll/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Wed May 10 11:22:56 2017 Benjamin
** Last update Sun May 21 15:56:55 2017 Benjamin
*/

#include <stdlib.h>
#include "bs.h"
#include "parser_ll.h"

static t_ast	*set_ast_right(t_ast *ast, char *type, char *value)
{
  t_ast		*new;

  if (!(new = malloc(sizeof(t_ast))))
    return (NULL);
  my_memset(new, 0, sizeof(t_ast));
  ast->right = new;
  new->father = ast;
  new->type = my_strdup(type);
  new->value = my_strdup(value);
  return (ast);
}

static t_ast	*ast_rec(t_ast *ast, t_token *token)
{
  if (!token->next && token->prev)
    return (set_ast_right(ast, token->type, token->value));
  if (!token->next && !token->prev)
    return (ast_arg(ast, token));
  if (!my_strcmp(token->type, "ARG"))
    ast = ast_arg(ast, token);
  else
    ast = ast_level(ast, token);
  token = token->next;
  return (ast_rec(ast, token));
}

t_ast	*set_ast(t_ast *ast, t_token *token)
{
  ast->type = my_strdup(token->type);
  ast->value = my_strdup(token->value);
  return (ast);
}

t_ast	*create_ast(t_ast *ast, t_token *token)
{
  if (!token)
    {
      if (!(ast = malloc(sizeof(t_ast))))
        return (NULL);
      my_memset(ast, 0, sizeof(t_ast));
      return (ast);
    }
  while (token->prev)
    token = token->prev;
  ast = ast_rec(ast, token);
  while (ast->father)
    ast = ast->father;
  return (ast);
}
