/*
** my_strdup_until.c for my_strdup_until in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May  2 19:22:02 2017 Arthur Knoepflin
** Last update Tue May  2 21:10:27 2017 Arthur Knoepflin
*/

#include <stdlib.h>

int	my_strlen_until(char *src, char sep)
{
  int	i;

  i = 0;
  while (src[i] && src[i] != sep)
    i += 1;
  return (i);
}

char	*my_strdup_until(char *src, char sep)
{
  int	i;
  char	*ret;

  if ((ret = malloc(sizeof(char) *
		    (my_strlen_until(src, sep) + 1))) == NULL)
    return (NULL);
  i = 0;
  while (src[i] && src[i] != sep)
    {
      ret[i] = src[i];
      i += 1;
    }
  ret[i] = '\0';
  return (ret);
}

int	my_strlen_until_x(char *src, char sep, int repeat)
{
  int	i;

  i = 0;
  while (src[i] && repeat >= 0)
    {
      if (src[i] == sep)
	repeat -= 1;
      if (repeat == -1)
	return (i);
      i += 1;
    }
  return (i);
}

char	*my_strdup_until_x(char *src, char sep, int repeat)
{
  int	i;
  char	*ret;

  if ((ret = malloc(sizeof(char) *
		    (my_strlen_until_x(src, sep, repeat) + 1))) == NULL)
    return (NULL);
  i = 0;
  while (src[i] && repeat >= 0)
    {
      if (src[i] == sep)
	repeat -= 1;
      if (repeat >= 0)
	{
	  ret[i] = src[i];
	  i += 1;
	}
    }
  ret[i] = '\0';
  return (ret);
}
