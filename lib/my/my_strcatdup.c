/*
** my_strcatdup.c for my_strcatdup in /home/arthur/delivery/PSU/PSU_2016_tetris
** 
** Made by 
** Login   <arthur@epitech.net>
** 
** Started on  Tue Feb 21 10:22:56 2017 
** Last update Sun May 14 17:48:23 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "my.h"

char	*my_strcatdup(char *s1, char *s2)
{
  int	i;
  int	j;
  char	*dest;
  int	len;

  i = 0;
  len = 0;
  if (s1 != NULL)
    len = my_strlen(s1);
  if ((dest = malloc(sizeof(char) * (len + my_strlen(s2) + 1))) == NULL)
    return (NULL);
  while (s1[i])
    {
      dest[i] = s1[i];
      i += 1;
    }
  j = 0;
  while (s2[j])
    {
      dest[i] = s2[j];
      i += 1;
      j += 1;
    }
  dest[i] = '\0';
  return (dest);
}
