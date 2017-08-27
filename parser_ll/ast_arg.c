/*
** ast_arg.c for ast in /home/benjamin/Dropbox/PSU_2016_42sh/parser_ll/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Thu May 11 15:53:09 2017 Benjamin
** Last update Fri May 19 15:00:34 2017 Benjamin
*/

#include <stdlib.h>
#include "bs.h"
#include "parser_ll.h"

static t_ast	*set_left(t_ast *ast, t_ast *new, t_token *token)
{
  new = set_ast(new, token);
  new->father = ast;
  ast->left = new;
  return (ast);
}

static t_ast	*set_right(t_ast *ast, t_ast *new, t_token *token)
{
  new = set_ast(new, token);
  new->father = ast;
  ast->right = new;
  return (ast);
}

t_ast	*ast_arg(t_ast *ast, t_token *token)
{
  t_ast	*new;

  if (!(new = malloc(sizeof(t_ast))))
    return (NULL);
  my_memset(new, 0, sizeof(t_ast));
  if (!ast)
    {
      return (set_ast(new, token));
    }
  if (!ast->left)
    return (set_left(ast, new, token));
  return (set_right(ast, new, token));
}
