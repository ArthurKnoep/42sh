/*
** ast_lvl.c for 42sh in /home/benjamin/Dropbox/PSU_2016_42sh/parser_ll/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Thu May 11 15:54:46 2017 Benjamin
** Last update Sun May 21 15:55:47 2017 Benjamin
*/

#include <stdlib.h>
#include "bs.h"
#include "parser_ll.h"

static int	check_level(t_ast *ast)
{

  if (!my_strcmp(ast->type, "OP_LOW"))
    return (3);
  if (!my_strcmp(ast->type, "REDIR"))
    return (2);
  if (!my_strcmp(ast->type, "OP_HIGH"))
    return (1);
  return (0);
}

static int	count_level_ast(t_ast *ast, int lvl_new)
{
  t_ast		*tmp;
  int		count;

  tmp = ast;
  count = 0;
  if (check_level(ast) == lvl_new)
    {
      return (0);
    }
  while (tmp->father && check_level(tmp) <= lvl_new &&
	 check_level(tmp->father) <= lvl_new)
    {
      tmp = tmp->father;
      count++;
    }
  return (count);
}

static t_ast	*set_ast_level(t_ast *ast, t_ast *new)
{
  int		lvl_new;
  int		count_ast;

  lvl_new = check_level(new);
  count_ast = count_level_ast(ast, lvl_new);
  if (count_ast || (!count_ast && lvl_new > check_level(ast)))
    return (rebuild_branch(ast, new, count_ast));
  if (!ast->father && check_level(new) >= check_level(ast))
    return (rebuild_branch_start(ast, new));
  return (create_simple_branch(ast, new));
}

t_ast	*ast_level(t_ast *ast, t_token *token)
{
  t_ast	*new;

  if (!(new = malloc(sizeof(t_ast))))
    return (NULL);
  my_memset(new, 0, sizeof(t_ast));
  set_ast(new, token);
  if (!ast)
    {
      return (new);
    }
  if (!my_strcmp(ast->type, "ARG") && !ast->father)
    {
      ast->father = new;
      new->left = ast;
      return (set_ast(new, token));
    }
  return (set_ast_level(ast, new));
}
