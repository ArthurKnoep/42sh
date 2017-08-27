/*
** parserll.c for 42sh in /home/benjamin/Dropbox/PSU_2016_42sh/builtins/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun May 21 16:21:35 2017 Benjamin
** Last update Mon May 22 09:44:02 2017 Benjamin
*/

#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "parser_ll.h"
#include "shell.h"
#include "my.h"

int	call_parser_ll(t_shell *shell, int args)
{
  char	*str;

  shell = shell;
  args = args;
  my_putstr("Type a CMD and see the Tree: ");
  str = get_next_line(0);
  if (!parser_ll(str))
    {
      free(str);
      return (1);
    }
  free(str);
  return (0);
}
