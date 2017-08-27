/*
** prompt_client.c for prompt_cli in /home/arthur/delivery/PSU/PSU_2016_42sh/dualcast
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May 18 11:53:43 2017 Arthur Knoepflin
** Last update Thu May 18 13:20:56 2017 Arthur Knoepflin
*/

#include "server.h"
#include "my.h"

char	*get_prompt_cli(t_client *client)
{
  char	*ret;

  ret = my_strdup("(\033[32;1m");
  if (client->name)
    {
      ret = my_fstrcat(ret, client->name, 1);
      ret = my_fstrcat(ret, "@", 1);
    }
  ret = my_fstrcat(ret, "DualCast\033[0m) $> ", 1);
  client->len_prompt = my_strlen(ret);
  return (ret);
}
