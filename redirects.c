/*
** redirects.c for minishell2 in /home/nicolaspolomack/psu/2/PSU_2016_minishell2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Mar 20 19:57:11 2017 Nicolas Polomack
** Last update Sun May 21 04:35:07 2017 Nicolas Polomack
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "shell.h"
#include "my.h"

int	setup_right_redirect(t_command *head, int *fds, int i)
{
  int	fd;

  (void)fds;
  if ((fd = open(head->r_name, O_WRONLY | O_CREAT |
                 (i ? O_TRUNC : O_APPEND), 0644)) == -1)
    {
      if (errno == EISDIR)
	{
	  my_print_err(head->r_name);
	  return (my_print_ret(": Is a directory.\n", -1));
	}
      else
	return (-1);
    }
  dup2(fd, 1);
  return (fd);
}

int	setup_left_redirect(char *name, int type)
{
  int	fd;
  int	i[2];

  if (!type)
    {
      if (pipe(i) == -1)
	return (-1);
      fd = i[0];
      if (isatty(0))
	my_putstr("$> ");
      return (buffer_input(name, i));
    }
  else
    if ((fd = open(name, O_RDONLY)) == -1)
      return (-1);
  return (fd);
}

int	prepare_redirect(t_command *head, char **type, char **name, int i)
{
  *type = head->av[i];
  if (!head->av[i + 1])
    return (my_print_ret("Missing name for redirect.\n", -1));
  *name = head->av[i + 1];
  while (head->av[++i + 1])
    head->av[i - 1] = head->av[i + 1];
  head->av[i - 1] = NULL;
  if (i == 1)
    return (my_print_ret("Invalid null command.\n", -1));
  return (0);
}

int	check_redirects(t_command *head, t_command *last)
{
  int	i;
  int	r;
  int	l;

  init_redirect(head, &r, &l, &i);
  while (head->av[++i])
    if (is_right_redirect(head->av[i]) ||
	is_left_redirect(head->av[i]))
      {
	if (head->av[i + 1] == NULL)
	  return (my_print_ret("Missing name for redirect.\n", -1));
	else
	  (is_left_redirect(head->av[i])) ? (l += 1) : (r += 1);
      }
  if (r > 1 || (r == 1 && head->link == '|'))
    return (my_print_ret("Ambiguous output redirect.\n", -1));
  else if (l > 1 || (l == 1 && last && last->link == '|'))
    return (my_print_ret("Ambiguous input redirect.\n", -1));
  return (0);
}

int		set_redirects(t_shell *shell)
{
  int		i;
  t_command	*head;
  t_command	*last;

  last = NULL;
  head = shell->commands;
  while (head)
    {
      if ((check_redirects(head, last)) == -1)
	return (-1);
      i = -1;
      while (head->av[++i])
	if (is_right_redirect(head->av[i]))
	  {
	    if (prepare_redirect(head, &head->r_type, &head->r_name, i--) == -1)
	      return (-1);
	  }
	else if (is_left_redirect(head->av[i]))
	  if (prepare_redirect(head, &head->l_type, &head->l_name, i--) == -1)
	    return (-1);
      last = head;
      head = head->next;
    }
  return (0);
}
