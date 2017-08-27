/*
** print_ast.c for 42sh in /home/benjamin/Dropbox/PSU_2016_42sh/parser_ll/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Fri May 12 13:19:33 2017 Benjamin
** Last update Sat May 20 10:57:14 2017 Benjamin
*/

#include <parser_ll.h>
#include <bs.h>

static void	rec_print(t_ast *ast)
{
  t_ast		*right;
  t_ast		*left;

  left = ast;
  right = ast;
  if (!ast)
    {
      printf("AST est NULL\n");
      return ;
    }
  printf(">> %s <<\n", ast->value);
  if (ast->left)
    {
      left = ast->left;
      printf("-Left-");
      rec_print(left);
    }
  if (ast->right)
    {
      right = ast->right;
      printf("-Right-");
      rec_print(right);
    }
  printf("!!! UP (Father) !!!\n");
}

void	print_ast(t_ast *ast)
{
  if (!ast)
    {
      printf("AST est NULL\n");
      return ;
    }
  printf("\n");
  while (ast->father)
    ast = ast->father;
  printf("====START====\n");
  rec_print(ast);
  printf("=====END=====\n");
}
