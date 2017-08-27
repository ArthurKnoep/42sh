/*
** tmp.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed May 17 15:47:48 2017 Nicolas Polomack
** Last update Sun May 21 04:26:13 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line.h"
#include "shell.h"
#include "my.h"

void	tmp_file(t_shell *shell)
{
  char	*name;
  char	*edit;
  char	*exec;
  int	fd;

  if ((edit = getenv("EDITOR")) == NULL ||
      (name = strdup("/tmp/42sh-tmpXXXXXX")) == NULL ||
      (fd = mkstemp(name)) == -1 ||
      asprintf(&exec, "%s %s", edit, name) == -1)
    return ;
  if (shell->line)
    dprintf(fd, "%s", shell->line);
  free(shell->line);
  my_putchar(10);
  quick_exec(shell, exec);
  if (shell->exit == 1)
    return ;
  lseek(fd, SEEK_SET, 0);
  while ((shell->line = get_next_line(fd)))
    {
      my_printf("%s\n", shell->line);
      exec_line(shell, 1);
    }
  close(fd);
  init_prompt(shell);
}
