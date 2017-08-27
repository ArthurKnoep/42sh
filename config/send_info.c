/*
** send_info.c for send_info in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May  2 18:21:00 2017 Arthur Knoepflin
** Last update Sun May 21 04:09:13 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "server.h"
#include "my.h"

static char	*get_resp(t_info_pc *info)
{
  char		*ret;

  ret = my_fstrcat("{\"hostname\" : \"", info->hostname, 3);
  ret = my_fstrcat(ret, "\", \"os\" : \"", 1);
  ret = (info->os) ? my_fstrcat(ret, info->os, 2) : ret;
  ret = my_fstrcat(ret, "\", \"platform\" : \"", 1);
  ret = (info->plateforme) ? my_fstrcat(ret, info->plateforme, 2) : ret;
  ret = my_fstrcat(ret, "\", \"version\" : \"", 1);
  ret = (info->version) ? my_fstrcat(ret, info->version, 2) : ret;
  ret = my_fstrcat(ret, "\", \"memory_total\" : ", 1);
  ret = my_fstrcat(ret, int_toc(info->mem_total), 2);
  ret = my_fstrcat(ret, ", \"memory_available\" : ", 1);
  ret = my_fstrcat(ret, int_toc(info->mem_available), 2);
  ret = my_fstrcat(ret, ", \"process\" : \"", 1);
  ret = (info->proco) ? my_fstrcat(ret, info->proco, 2) : ret;
  return (my_fstrcat(ret, "\"}", 1));
}

void		send_info(t_socket client, t_config *config, char **arg)
{
  char		*resp;
  t_info_pc	*info;

  (void)config;
  (void)arg;
  if ((info = get_info()) == NULL)
    {
      write_client(client, ERROR_RESP);
      return ;
    }
  write_client(client, HEAD_RESP);
  write_client(client, "Content-type: application/json\r\n\r\n");
  resp = get_resp(info);
  write_client(client, resp);
  free(info);
  free(resp);
}
