/*
** send_env.c for send_env in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sat Apr 22 21:32:22 2017 Arthur Knoepflin
** Last update Sun May 21 21:12:23 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "server.h"
#include "shell.h"
#include "my.h"

static int	get_len(char *str)
{
  int		ret;
  int		i;

  i = 0;
  ret = 0;
  while (str[i])
    {
      if (str[i] == '\\')
      	ret += 1;
      ret += 1;
      i += 1;
    }
  return (ret);
}

char	*encode_bs(char *str)
{
  char	*ret;
  int	j;
  int	i;

  if ((ret = malloc(sizeof(char) * (get_len(str) + 1))) == NULL)
    return (NULL);
  ret[get_len(str)] = '\0';
  i = 0;
  j = 0;
  while (str[i])
    {
      ret[j] = str[i];
      if (str[i] == '\\')
	{
	  j += 1;
	  ret[j] = '\\';
	}
      j += 1;
      i += 1;
    }
  free(str);
  return (ret);
}

void	send_env(t_socket client, t_config *config, char **arg)
{
  char	*send;
  int	i;

  (void)config;
  (void)arg;
  i = 0;
  send = my_strdup("[");
  while (environ[i])
    {
      send = my_fstrcat(send, "\"", 1);
      send = my_fstrcat(send, environ[i], 1);
      send = my_fstrcat(send, "\"", 1);
      if (environ[i + 1])
	send = my_fstrcat(send, ",\n", 1);
      i += 1;
    }
  send = my_fstrcat(send, "]", 1);
  send = encode_bs(send);
  write_client(client, HEAD_RESP);
  write_client(client, "Content-type: application/json\r\n\r\n");
  write_client(client, send);
  free(send);
}
