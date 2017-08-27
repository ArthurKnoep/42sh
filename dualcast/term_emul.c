/*
** term_emul.c for term_emul in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon May  8 18:23:09 2017 Arthur Knoepflin
** Last update Thu May 18 13:08:59 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "my.h"

void	del_last_char(int len_prompt, char **prompt, int *len)
{
  *len = my_strlen(*prompt) - 11;
  if (my_strlen(*prompt) > len_prompt)
    *prompt = my_strndup(*prompt, my_strlen(*prompt) - 1);
}

void	add_char_dc(char **prompt, char c, int *len)
{
  insert_char(prompt, c);
  *len = my_strlen(*prompt) - 11;
}

void	del_prompt(int nb_char)
{
  int	i;
  char	space[nb_char + 1];

  i = 0;
  while (i < nb_char)
    {
      space[i] = ' ';
      i += 1;
    }
  space[i] = '\0';
  my_printf("\r%s", space);
}

void	send_char(t_socket sock, char c)
{
  char	*buf;
  char	send[7];

  strcpy(send, "char:");
  send[5] = c;
  send[6] = '\0';
  write_socket(sock, send);
  read_socket(sock, &buf);
  free(buf);
}
