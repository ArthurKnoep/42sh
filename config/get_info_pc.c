/*
** get_info_pc.c for get_info_pc in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May  2 17:20:13 2017 Arthur Knoepflin
** Last update Sun May 21 04:06:26 2017 Nicolas Polomack
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "server.h"
#include "get_next_line.h"

int	parse_info_version(t_info_pc *ret, int fd)
{
  char	*tmp;

  ret->version = NULL;
  ret->os = NULL;
  while ((tmp = get_next_line(fd)))
    {
      if (!my_strncmp("NAME=", tmp, 5))
	ret->os = my_strndup(tmp + 6, my_strlen(tmp) - 7);
      if (!my_strncmp("VERSION=", tmp, 8))
	ret->version = my_strndup(tmp + 9, my_strlen(tmp) - 10);
      free(tmp);
    }
  return (0);
}

int	parse_version(t_info_pc *ret)
{
  int	fd;

  if ((fd = open("/etc/os-release", O_RDONLY)) == -1)
    return (1);
  get_next_line(-1);
  parse_info_version(ret, fd);
  ret->plateforme = my_strdup("Linux");
  close(fd);
  if ((fd = open("/etc/hostname", O_RDONLY)) == -1)
    return (1);
  get_next_line(-1);
  ret->hostname = get_next_line(fd);
  close(fd);
  return (0);
}

int	parse_ram(t_info_pc *ret, int i)
{
  char	*str;
  int	fd;

  if ((fd = open("/proc/meminfo", O_RDONLY)) == -1)
    return (1);
  while ((str = get_next_line(fd)))
    {
      if (!my_strncmp(str, "MemTotal:", 9))
	{
	  i = 9;
	  while (str[i] && !(str[i] >= '0' && str[i] <= '9'))
	    i += 1;
	  ret->mem_total = my_getnbr(str + i);
	}
      if (!my_strncmp(str, "MemAvailable:", 13))
	{
	  i = 13;
	  while (str[i] && !(str[i] >= '0' && str[i] <= '9'))
	    i += 1;
	  ret->mem_available = my_getnbr(str + i);
	}
      free(str);
    }
  close(fd);
  return (0);
}

int	parse_proco(t_info_pc *ret)
{
  char	*str;
  int	fd;
  int	i;

  if ((fd = open("/proc/cpuinfo", O_RDONLY)) == -1)
    return (1);
  while ((str = get_next_line(fd)))
    {
      if (!my_strncmp(str, "model name", 10))
	{
	  i = 10;
	  while (str[i] && str[i] != ':')
	    i += 1;
	  i += 2;
	  ret->proco = my_strdup(str + i);
	  free(str);
	  close(fd);
	  return (0);
	}
      free(str);
    }
  close(fd);
  return (0);
}

t_info_pc	*get_info(void)
{
  t_info_pc	*ret;

  if ((ret = malloc(sizeof(t_info_pc))) == NULL)
    return (NULL);
  my_memset(ret, 0, sizeof(t_info_pc));
  if (parse_version(ret))
    return (NULL);
  if (parse_ram(ret, 0))
    return (NULL);
  if (parse_proco(ret))
    return (NULL);
  return (ret);
}
