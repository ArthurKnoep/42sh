/*
** dualcast.c for dualcast in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May  5 11:39:08 2017 Arthur Knoepflin
** Last update Sun May 21 04:14:36 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "get_next_line.h"
#include "server.h"
#include "shell.h"
#include "my.h"

int		launch_dc_server()
{
  fd_set	rdfs;
  t_socket	socket;
  t_socket	client;
  char		*code;

  if ((code = get_password()) == NULL)
    return (1);
  if (init_dualcast(&socket) == -1)
    return (1);
  my_printf("DualCast ready\nYour session token is : %s\n", code);
  if ((client = wait_connection(socket, &rdfs, code)) == -1)
    return (1);
  core_server_dc(socket, client, &rdfs);
  free(code);
  close(client);
  close(socket);
  my_printf("End of session\n");
  return (0);
}

static int	launch_dc_client(char *addr)
{
  t_client	client;

  if (init_connect_dc(addr, &client))
    return (1);
  if (my_strlen(client.name) == 0)
    client.name = NULL;
  core_client_dc(&client);
  close(client.sock);
  free(client.name);
  return (0);
}

int	launch_dualcast(t_shell *shell, int args)
{
  if (args >= 2 && !my_strcmp(shell->cur->av[1], "start"))
    launch_dc_server();
  else if (args >= 3 && !my_strcmp(shell->cur->av[1], "connect"))
    launch_dc_client(shell->cur->av[2]);
  else
    my_printf("Usage : dualcast [start | connect addr_ip]\n");
  return (0);
}
