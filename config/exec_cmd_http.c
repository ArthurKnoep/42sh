/*
** exec_cmd_http.c for exec_cmd_http in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed Apr 26 23:40:25 2017 Arthur Knoepflin
** Last update Sun May 21 11:31:55 2017 Arthur Knoepflin
*/

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "shell.h"
#include "my.h"

char	*get_cmd_exc(char *cmd_path, char *cmd)
{
  char	*tmp;

  if (cmd_path && !my_strcmp(cmd_path, "emacs"))
    return (my_strdup(cmd));
  else
    {
      tmp = my_strcatdup("timeout 1 ", cmd);
      return (tmp);
    }
}

static int	execute_http(t_socket client,
			     char *cmd)
{
  t_shell	shell;
  int		sauv;
  int		sauv2;

  init_shell(&shell);
  shell.line = cmd;
  if ((sauv = dup(1)) == -1)
    return (1);
  if ((sauv2 = dup(2)) == -1)
    return (1);
  if (dup2(client, 1) == -1)
    return (1);
  if (dup2(client, 2) == -1)
    return (1);
  exec_line(&shell, 0);
  dup2(sauv, 1);
  dup2(sauv2, 2);
  close(sauv);
  close(sauv2);
  return (0);
}

static int	change_dir_http(t_socket client, char **cmd_p)
{
  if (nb_args(cmd_p) >= 2)
    {
      if (chdir(cmd_p[1]) == -1)
	write_client(client, strerror(errno));
      else
	{
	  write_client(client, "Change to ");
	  write_client(client, cmd_p[1]);
	}
    }
  else
    write_client(client, "Error: precise a folder");
  return (0);
}

void	exec_cmd_http(t_socket client, t_config *config, char **arg)
{
  char	*cmd;
  char	**cmd_p;

  (void)config;
  if (nb_args(arg) >= 4)
    {
      if ((cmd = malloc(sizeof(char) * (my_strlen(arg[3]) + 1))) == NULL)
	return ;
      urldecode(arg[3], cmd);
      if ((cmd_p = my_split_char(cmd, ' ')) == NULL)
	return ;
      write_client(client, BASE_RESP);
      if (!my_strcmp(cmd_p[0], "cd"))
	change_dir_http(client, cmd_p);
      else
	execute_http(client, cmd);
    }
  else
    write_client(client, ERROR_RESP);
}
