/*
** prompt.c for prompt in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sat Apr 29 22:28:04 2017 Arthur Knoepflin
** Last update Sun May 21 04:08:08 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "server.h"
#include "my.h"

void	send_prompt_sel(t_socket client, t_config *config, char **arg)
{
  char	*selected;

  (void)arg;
  if ((selected = int_toc(config->prompt)) == NULL)
    return ;
  write_client(client, BASE_RESP);
  write_client(client, selected);
  free(selected);
}

void	update_prompt_sel(t_socket client, t_config *config, char **arg)
{
  config->prompt = my_getnbr(arg[3]);
  write_client(client, BASE_RESP);
}
