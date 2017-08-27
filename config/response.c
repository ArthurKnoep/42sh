/*
** response.c for response in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sat Apr 22 14:33:57 2017 Arthur Knoepflin
** Last update Fri May 19 19:42:34 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "shell.h"
#include "my.h"

static int	strlen_space(char *str)
{
  int		i;

  str += 4;
  i = 0;
  while (str && str[i] && str[i] != ' ')
    i += 1;
  return (i - 6);
}

static char	*get_arg(char *head)
{
  char		**resp;
  char		**req;
  char		*ret;
  int		i;

  resp = my_split(head, "\r\n\r\n");
  if (resp)
    {
      req = my_split(resp[0], "\r\n");
      if (req && !my_strncmp(req[0], "GET", 3))
	{
	  i = 0;
	  while (req[0][i] && req[0][i] != '?')
	    i += 1;
	  i += 1;
	  ret = my_strndup(req[0] + i, strlen_space(req[0]));
	  free_tab(req);
	  free_tab(resp);
	  return (ret);
	}
      free_tab(req);
      free_tab(resp);
    }
  return (NULL);
}

static int	parse_arg(t_socket client, char **arg, t_config *config)
{
  void		(*request_tab[nb_request()])(t_socket, t_config *, char **);
  int		idx;

  idx = indexof_request(arg[1]);
  get_tab_request(request_tab);
  if (idx >= 0 && idx < nb_request())
    request_tab[idx](client, config, arg);
  else
    write_client(client, BASE_RESP);
  free_tab(arg);
  if (idx == 0)
    return (1);
  return (0);
}

int	response(t_socket client, char *buf, t_config *config)
{
  char	*file;
  char	*r_arg;
  char	**arg;

  if ((file = get_file_http(buf)) == NULL)
    return (1);
  r_arg = getenv("CFG_PATH");
  if (!my_strncmp(file + 1, MAGIC, my_strlen(MAGIC)))
    {
      if ((r_arg = get_arg(buf)) && (arg = my_split_mulchar(r_arg, "&=")))
	if (!my_strcmp(arg[0], "arg"))
	  {
	    free(r_arg);
	    free(file);
	    return (parse_arg(client, arg, config));
	  }
    }
  else
    send_file_http(client, my_fstrcat(r_arg ? r_arg : PATH_DOC, file, 0));
  free(file);
  return (0);
}
