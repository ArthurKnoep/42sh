/*
** com_serv.c for com_serv in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sun Apr 23 10:32:34 2017 Arthur Knoepflin
** Last update Sun May  7 17:49:26 2017 Arthur Knoepflin
*/

#include <stdio.h>
#include "server.h"
#include "my.h"

int	read_client(t_socket sock, char *buffer)
{
  int	n;

  n = 0;
  if ((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
    {
      perror("recv()");
      n = 0;
    }
  buffer[n] = 0;
  return (n);
}

void	write_client(t_socket sock, char *buffer)
{
  if (send(sock, buffer, my_strlen(buffer), 0) < 0)
    perror("send()");
}
