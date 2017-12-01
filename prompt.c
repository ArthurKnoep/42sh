/*
** prompt.c for prompt in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May  4 23:33:54 2017 Arthur Knoepflin
** Last update Tue Jul 24 01:14:13 2017 nicolaspolomack
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "prompt.h"
#include "get_next_line.h"
#include "shell.h"

char	*get_hostname(void)
{
  char	*ret;
  int	fd;

  if ((fd = open("/etc/hostname", O_RDONLY)) == -1)
    return (NULL);
  ret = get_next_line(fd);
  close(fd);
  return (ret);
}

static void	get_tab_prompt(void (*tab_prompt[8])(t_shell *))
{
  tab_prompt[0] = &turbosh_prompt;
  tab_prompt[1] = &bash_prompt;
  tab_prompt[2] = &tcsh_prompt;
  tab_prompt[3] = &minimalist_prompt;
  tab_prompt[4] = &ketchup_prompt;
  tab_prompt[5] = &bigmac_prompt;
  tab_prompt[6] = &oh_my_zsh;
  tab_prompt[7] = &mysh;
}

void	print_prompt(t_shell *shell)
{
  void	(*tab_prompt[8])(t_shell *);

  get_tab_prompt(tab_prompt);
  if (shell->prompt >= 0 && shell->prompt < 8)
    tab_prompt[shell->prompt](shell);
  else
    tab_prompt[0](shell);
}

void	get_prompt(t_shell *shell)
{
  char	*str;

  shell->prompt = 0;
  if ((str = getenv("PROMPT")) != NULL)
    shell->prompt = strtol(str, NULL, 10);
}
