/*
** get_file_http.c for get_file_http in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon Apr 24 15:38:43 2017 Arthur Knoepflin
** Last update Sat Apr 29 16:14:43 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "server.h"
#include "my.h"

char	*special_case(char *ret)
{
  if (!my_strcmp(ret, "/"))
    {
      free(ret);
      return (my_strdup("/index.html"));
    }
  if (!my_strcmp(ret, "/help"))
    {
      free(ret);
      return (my_strdup("/help.html"));
    }
  if (!my_strcmp(ret, "/privacy"))
    {
      free(ret);
      return (my_strdup("/privacy.html"));
    }
  return (NULL);
}

char	*get_file_http(char *buf)
{
  char	*ret;
  char	*spec;
  int	i;

  if (my_strncmp(buf, "GET", 3))
    return (NULL);
  buf += 4;
  i = 0;
  while (buf[i] && buf[i] != ' ')
    i += 1;
  ret = my_strndup(buf, i);
  if ((spec = special_case(ret)) != NULL)
    return (spec);
  return (ret);
}
