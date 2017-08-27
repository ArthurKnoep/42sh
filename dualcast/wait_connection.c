/*
** wait_connection.c for wait_connection in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May  5 16:02:42 2017 Arthur Knoepflin
** Last update Sun May 21 04:20:01 2017 Nicolas Polomack
*/

#include <sys/select.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "my.h"
#include "get_next_line.h"

static char	*read_code(t_socket client)
{
  char		*ret;
  int		len;

  if ((ret = malloc(sizeof(char) * 5)) == NULL)
    return (NULL);
  if ((len = recv(client, ret, 4, 0)) < 0)
    return (NULL);
  ret[len] = '\0';
  return (ret);
}

static void	send_login(t_socket sock)
{
  char		*login;
  char		*str;

  if ((login = getenv("LOGNAME")))
    {
      if ((str = my_fstrcat("OK:", login, 0)))
	{
	  write_socket(sock, str);
	  free(str);
	}
    }
  else
    write_socket(sock, "OK:");
}

static int	new_client_dc(t_socket sock,
			      fd_set *rdfs,
			      t_socket *client,
			      char *passwd)
{
  socklen_t	len;
  t_sockaddr_in	csin;
  char		*recv_code;

  len = sizeof(csin);
  if ((*client = accept(sock, &csin, &len)) == -1)
    {
      close(*client);
      return (0);
    }
  FD_SET(*client, rdfs);
  recv_code = read_code(*client);
  if (!my_strcmp(recv_code, passwd))
    {
      my_printf("Une personne c'est connecté\n");
      send_login(*client);
      return (1);
    }
  my_printf("Une personne n'a pas réussi à se connecter\n");
  send(*client, "KO", 2, 0);
  close(*client);
  return (0);
}

t_socket	wait_connection(t_socket sock, fd_set *rdfs, char *passwd)
{
  t_socket	client;
  int		stop;

  stop = 0;
  client = 8;
  while (!stop)
    {
      FD_ZERO(rdfs);
      FD_SET(STDIN_FILENO, rdfs);
      FD_SET(sock, rdfs);
      FD_SET(client, rdfs);
      if (select(sock + 1, rdfs, NULL, NULL, NULL) == -1)
	return (-1);
      if (FD_ISSET(STDIN_FILENO, rdfs))
	stop = 2;
      else if (FD_ISSET(sock, rdfs))
	stop = new_client_dc(sock, rdfs, &client, passwd);
    }
  if (stop == 2)
    {
      close(sock);
      free(get_next_line(0));
      return (-1);
    }
  return (client);
}

