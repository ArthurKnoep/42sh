/*
** prompt.c for prompt in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May 16 17:52:03 2017 Arthur Knoepflin
** Last update Tue Jul 24 01:22:01 2017 nicolaspolomack
*/

#include <stdlib.h>
#include "get_next_line.h"
#include "prompt.h"
#include "my.h"

static void	show_prompt(t_shell *shell)
{
  my_printf("0 : TurboSh        : ");
  turbosh_prompt(shell);
  my_printf("\n1 : Bash           : ");
  bash_prompt(shell);
  my_printf("\n2 : TCSH           : ");
  tcsh_prompt(shell);
  my_printf("\n3 : minimalist     : ");
  minimalist_prompt(shell);
  my_printf("\n4 : Tomato Ketchup : ");
  ketchup_prompt(shell);
  my_printf("\n5 : Big Mac        : ");
  bigmac_prompt(shell);
  my_printf("\n6 : Oh My Zsh      : ");
  oh_my_zsh(shell);
  my_printf("\n7 : Mysh           : ");
  mysh(shell);
  my_printf("\n");
}

int	prompt(t_shell *shell, int args)
{
  int	stop;
  char	*choice;

  (void)args;
  show_prompt(shell);
  stop = 0;
  while (!stop)
    {
      my_printf("Make your choice : ");
      if (!(choice = get_next_line(0)) && my_printf("\n"))
	return (1);
      if (is_num(choice) && atoi(choice) >= 0 && atoi(choice) <= 7)
	{
	  shell->prompt = my_getnbr(choice);
	  setenv("PROMPT", choice, 1);
	  free(choice);
	  return (0);
	}
      my_printf("Nope\n");
      free(choice);
    }
  return (0);
}
