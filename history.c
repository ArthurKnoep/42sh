/*
** history.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu May 11 20:41:13 2017 Nicolas Polomack
** Last update Sun May 21 04:22:48 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include "server.h"
#include "shell.h"
#include "my.h"

void		write_hist(t_shell *shell, int fd)
{
  t_history	*head;
  int		i;
  int		c;

  head = shell->hist.last;
  c = -1;
  while (head->prev && ++c < 500)
    head = head->prev;
  while (head)
    {
      i = -1;
      while (head->cmd[++i])
	dprintf(fd, i ? " %s" : "%s", head->cmd[i]);
      dprintf(fd, "\n");
      head = head->next;
      c += 1;
    }
  close(fd);
  free_hist(shell);
}

void		save_history(t_shell *shell)
{
  int		fd;
  char		*line;

  if (shell->hist.first == NULL || shell->home == NULL ||
      (line = malloc(512)) == NULL)
    return ;
  line[0] = 0;
  line = strcat(line, shell->home);
  if (shell->home[strlen(shell->home)] != '/')
    line[strlen(shell->home)] = '/';
  line[strlen(shell->home) + 1] = 0;
  line = my_strcat(line, HIST_FILE);
  if ((fd = open(line, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    return ;
  free(line);
  write_hist(shell, fd);
}

int		disp_hist(t_shell *shell, int args)
{
  t_history	*head;
  int		i;
  int		index;

  (void)args;
  if (shell->hist.first == NULL)
    return (0);
  index = 0;
  head = shell->hist.first;
  while (head)
    {
      index += 1;
      printf("%6d   ", index);
      i = -1;
      while (head->cmd[++i])
	printf(i ? " %s" : "%s", head->cmd[i]);
      printf("\n");
      head = head->next;
    }
  return (0);
}

void	add_hist_elem(t_shell *shell, char *line)
{
  t_history	*elem;

  if ((elem = malloc(sizeof(t_history))) == NULL ||
      (elem->cmd = my_split_mulchar(line, " \t")) == NULL)
    handle_error("malloc");
  elem->next = NULL;
  elem->prev = NULL;
  if (shell->hist.last)
    {
      shell->hist.last->next = elem;
      elem->prev = shell->hist.last;
      shell->hist.last = elem;
    }
  else
    {
      shell->hist.first = elem;
      shell->hist.last = elem;
    }
}

void	init_history(t_shell *shell)
{
  int	fd;
  char	*line;

  shell->hist.cur = NULL;
  shell->hist.last = NULL;
  shell->hist.first = NULL;
  if (shell->home == NULL)
    return ;
  if ((line = malloc(512)) == NULL)
    handle_error("malloc");
  line[0] = 0;
  line = strcat(line, shell->home);
  if (shell->home[strlen(shell->home)] != '/')
    line[strlen(shell->home)] = '/';
  line[strlen(shell->home) + 1] = 0;
  line = my_strcat(line, HIST_FILE);
  if ((fd = open(line, O_RDONLY)) == -1)
    return ;
  free(line);
  while ((line = get_next_line(fd)))
    {
      add_hist_elem(shell, line);
      free(line);
    }
  close(fd);
}
