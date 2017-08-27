/*
** parser_ll.h for 42sh in /home/benjamin/Dropbox/PSU_2016_42sh/include/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Tue May  2 16:59:49 2017 Benjamin
** Last update Mon May 15 09:54:35 2017 Benjamin
*/

#ifndef PARSER_LL_H_
# define PARSER_LL_H_

# define OP_LOW "; && ||"
# define REDIR "> >> << <"
# define OP_HIGH "|"

typedef struct	s_token t_token;
typedef struct	s_ast t_ast;
typedef struct	s_grammar t_grammar;

struct		s_grammar
{
  char		**op_high;
  char		**op_low;
  char		**redir;
};

struct		s_token
{
  char		*type;
  char		*value;
  t_token	*next;
  t_token	*prev;
};

struct		s_ast
{
  char		*type;
  char		*value;
  t_ast		*father;
  t_ast		*left;
  t_ast		*right;
};

void		print_ast(t_ast *ast);
t_ast		*parser_ll(char *);
t_token		*fill_token(t_token *, char *);
t_ast		*ast_level(t_ast *, t_token *);
t_ast		*ast_arg(t_ast *, t_token *);
t_ast		*set_ast(t_ast *ast, t_token *);
t_ast		*create_ast(t_ast *, t_token *);
t_ast		*create_simple_branch(t_ast *ast, t_ast *new);
t_ast		*rebuild_branch_start(t_ast *ast, t_ast *new);
t_ast		*rebuild_branch(t_ast *ast, t_ast *new, int lvl_ast);
int		set_arg(t_token **, t_grammar *, char **, int *);
int		check_op_high(t_token **, t_grammar *, char **, int *);
int		check_op_low(t_token **, t_grammar *, char **, int *);
int		check_redir(t_token **, t_grammar *, char **, int *);

#endif /* !PARSER_LL_H_ */
