/*
** init_connection.c for init_connection in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sun Apr 23 11:23:51 2017 Arthur Knoepflin
** Last update Wed May 24 09:46:57 2017 Arthur Knoepflin
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int		init_dualcast(t_socket *sock)
{
  t_sockaddr_in	sin;

  if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    return (-1);
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(DUALCAST_PORT);
  sin.sin_family = AF_INET;
  if (bind(*sock, (t_sockaddr *) &sin, sizeof (sin)) == SOCKET_ERROR)
    {
      perror("bind ");
      return (-1);
    }
  if (listen(*sock, MAX_CLIENTS) == SOCKET_ERROR)
    return (-1);
  return (1);
}
