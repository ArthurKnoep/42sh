/*
** send_mime.c for send_mime in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon Apr 24 17:21:30 2017 Arthur Knoepflin
** Last update Tue May 16 11:27:48 2017 Arthur Knoepflin
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "server.h"
#include "get_next_line.h"
#include "my.h"

static char	*ext(char *path)
{
  int		i;

  i = my_strlen(path) - 1;
  while (i >= 0 && path[i] != '.')
    i -= 1;
  return (path + i + 1);
}

static char	*get_mime(int fd, char *ext)
{
  char		*tmp;
  char		*ret;

  while ((tmp = get_next_line(fd)))
    {
      if (!my_strncmp(tmp, ext, my_strlen(ext)))
	{
	  ret = my_strdup(tmp + my_strlen(ext) + 1);
	  free(tmp);
	  return (ret);
	}
      free(tmp);
    }
  return (my_strdup("text/plain"));
}

void	send_mime(t_socket sock, char *path)
{
  char	*ex;
  char	*mime;
  int	fd;

  if ((ex = ext(path)) == NULL)
    return ;
  if ((fd = open(MIMETYPE, O_RDONLY)) == -1)
    return ;
  mime = get_mime(fd, ex);
  close(fd);
  write_client(sock, "Content-type: ");
  write_client(sock, (mime) ? mime : "");
  write_client(sock, CRLF);
  free(mime);
}
