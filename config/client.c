/*
** client.c for client in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sun Apr 23 12:05:25 2017 Arthur Knoepflin
** Last update Sun May 21 11:27:36 2017 Arthur Knoepflin
*/

#include <stdio.h>
#include <string.h>
#include "server.h"
#include "my.h"

void	remove_client(t_socket *clients, int to_remove, int *actual)
{
  memmove(clients + to_remove,
	  clients + to_remove + 1,
	  (*actual - to_remove - 1) * sizeof(t_socket));
  (*actual)--;
}

static int	limit_client(int actual, t_socket csock)
{
  if (actual >= MAX_CLIENTS)
    {
      my_putstr("Too many clients in the same time\
: Automatic deconnexion\n");
      close(csock);
      return (1);
    }
  else
    return (0);
}

int		new_client(t_socket *clients,
			   int *actual,
			   fd_set *rdfs,
			   t_socket sock)
{
  t_sockaddr_in	csin;
  socklen_t	sinsize;
  t_socket	csock;

  sinsize = sizeof(csin);
  if ((csock = accept(sock, (t_sockaddr *)&csin, &sinsize)) == SOCKET_ERROR)
    {
      perror("");
      return (1);
    }
  if (limit_client(*actual, csock))
    return (1);
  FD_SET(csock, rdfs);
  clients[*actual] = csock;
  *actual += 1;
  return (0);
}

static void	client_disconnect(t_socket *clients, int *actual, int i)
{
  closesocket(clients[i]);
  remove_client(clients, i, actual);
}

int	client_talk(t_socket *clients,
		    int *actual,
		    fd_set *rdfs,
		    t_config *config)
{
  int	i;
  int	ret;
  int	len;
  char	buffer[BUF_SIZE];

  i = 0;
  while (i < *actual)
    {
      if (FD_ISSET(clients[i], rdfs))
	{
	  len = read_client(clients[i], buffer);
	  if (len == 0)
	    client_disconnect(clients, actual, i);
	  else
	    {
	      ret = response(clients[i], buffer, config);
	      client_disconnect(clients, actual, i);
	      if (ret == 1)
		return (1);
	    }
	}
      i += 1;
    }
  return (0);
}
