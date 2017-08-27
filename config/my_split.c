/*
** my_split.c for my_split in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sat Apr 22 14:09:15 2017 Arthur Knoepflin
** Last update Sat Apr 22 14:21:36 2017 Arthur Knoepflin
*/

#include <string.h>
#include <stdlib.h>

int	is_sep(char *c, char *sep)
{
  if (!strncmp(c, sep, strlen(sep)))
    return (1);
  return (0);
}

int	nb_par(char *str, char *sep)
{
  int	i;
  int	count;

  i = 0;
  count = 0;
  while (str[i])
    {
      if (!is_sep(str + i, sep))
	{
	  count += 1;
	  while (str[i] && !is_sep(str + i, sep))
	    i += 1;
	}
      if (str[i])
	i += 1;
    }
  return (count);
}

int	index_child(char *str, char *sep, int index)
{
  int	i;
  int	count;

  i = 0;
  count = 0;
  while (str[i] && is_sep(str + i, sep) && ++i);
  while (str[i] && count < index)
    {
      if (!is_sep(str + i, sep))
	{
	  count += 1;
	  while (str[i] && !is_sep(str + i, sep))
	    i += 1;
	  if (str[i])
	    i += 1;
	}
      while (str[i] && is_sep(str + i, sep) && i++);
    }
  if (is_sep(str + i, sep))
    i += 1;
  if (index != 0)
    return (i + strlen(sep) - 1);
  else
    return (i);
}

int	len_child(char *str, char *sep, int index)
{
  int	i;
  int	count;

  i = index_child(str, sep, index);
  count = 0;
  while (str[i] && !is_sep(str + i, sep))
    {
      count += 1;
      i += 1;
    }
  return (count);
}

char	**my_split(char *str, char *sep)
{
  int	i;
  int	j;
  int	index;
  char	**ret;

  if (str == NULL)
    return (NULL);
  if ((ret = malloc(sizeof(char *) * (nb_par(str, sep) + 1))) == NULL)
    return (NULL);
  ret[nb_par(str, sep)] = NULL;
  i = -1;
  while (++i < nb_par(str, sep))
    {
      j = 0;
      ret[i] = malloc(sizeof(char) * (len_child(str, sep, i) + 1));
      ret[i][len_child(str, sep, i)] = '\0';
      index = index_child(str, sep, i);
      while (j < len_child(str, sep, i))
      	{
      	  ret[i][j] = str[index];
      	  index += 1;
      	  j += 1;
      	}
    }
  return (ret);
}
