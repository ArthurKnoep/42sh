/*
** ast_lvl_build_branch.c for 42sh in /home/benjamin/Dropbox/PSU_2016_42sh/parser_ll/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Fri May 12 10:13:21 2017 Benjamin
** Last update Sun May 21 17:58:32 2017 Arthur Knoepflin
*/

#include "parser_ll.h"
#include "bs.h"

t_ast	*rebuild_branch(t_ast *ast, t_ast *new, int count_ast)
{
  t_ast	*tmp;
  t_ast	*father;

  tmp = ast;
  while (tmp->father && count_ast > 0)
    {
      tmp = tmp->father;
      count_ast--;
    }
  if (!tmp->father)
    return (rebuild_branch_start(tmp, new));
  father = tmp->father;
  new->father = father;
  if (father->right == tmp)
    father->right = new;
  else
    father->left = new;
  new->left = tmp;
  tmp->father = new;
  return (new);
}

t_ast	*create_simple_branch(t_ast *ast, t_ast *new)
{
  new->father = ast;
  if (!ast->left)
    {
      ast->left = new;
      ast = ast->left;
    }
  else if (!ast->right)
    {
      ast->right = new;
      ast = ast->right;
    }
  else
    {
      new->left = ast->right;
      ast->right->father = new->left;
      ast->right = new;
      ast = ast->right;
    }
  return (ast);
}

t_ast	*rebuild_branch_start(t_ast *ast, t_ast *new)
{
  new->left = ast;
  ast->father = new;
  return (new);
}
