/*
** get_request.c for get_request in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 17 10:28:17 2017 Arthur Knoepflin
** Last update Sun May 21 04:07:08 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "shell.h"
#include "server.h"
#include "my.h"

static const char	*request_tab[] =
  {
    "quit",
    "get_env",
    "get_info",
    "add_env",
    "update_env",
    "del_env",
    "exec",
    "get_prompt_sel",
    "update_prompt_sel",
    NULL
  };

int	nb_request()
{
  int	i;

  i = 0;
  while (request_tab[i])
    i += 1;
  return (i);
}

int	indexof_request(char *str)
{
  int	i;

  i = 0;
  while (request_tab[i])
    {
      if (!my_strcmp(str, (char *) request_tab[i]))
	return (i);
      i += 1;
    }
  return (-1);
}

void	get_tab_request(void (**request_tab)(t_socket, t_config *, char **))
{
  request_tab[0] = &exit_config;
  request_tab[1] = &send_env;
  request_tab[2] = &send_info;
  request_tab[3] = &add_env_http;
  request_tab[4] = &update_env_http;
  request_tab[5] = &del_env_http;
  request_tab[6] = &exec_cmd_http;
  request_tab[7] = &send_prompt_sel;
  request_tab[8] = &update_prompt_sel;
}
