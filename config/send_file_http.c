/*
** send_file_http.c for send_file_http.c in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon Apr 24 16:14:59 2017 Arthur Knoepflin
** Last update Tue May 16 10:59:31 2017 Arthur Knoepflin
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "my.h"

int	read_file(char *path, char *ret, int size, t_socket client)
{
  int	len;
  int	fd;

  if ((fd = open(path, O_RDONLY)) == -1)
    {
      write_client(client, FB_RESP);
      return (1);
    }
  len = read(fd, ret, size);
  ret[len] = 0;
  close(fd);
  return (0);
}

static void	send_length(t_socket sock, int size)
{
  char		*toc;

  toc = int_toc(size);
  write_client(sock, toc);
  free(toc);
}

void		send_file_http(t_socket sock, char *path)
{
  char		*buf;
  struct stat	stati;

  if (stat(path, &stati) == -1)
    {
      write_client(sock, NF_RESP);
      return ;
    }
  if ((buf = malloc(sizeof(char) * (stati.st_size + 1))) == NULL)
    {
      write_client(sock, ERROR_RESP);
      return ;
    }
  if (read_file(path, buf, stati.st_size, sock))
    return ;
  write_client(sock, HEAD_RESP);
  write_client(sock, "Content-length: ");
  send_length(sock, stati.st_size);
  write_client(sock, CRLF);
  send_mime(sock, path);
  write_client(sock, "\r\n");
  send(sock, buf, stati.st_size, 0);
  free(buf);
  free(path);
}
