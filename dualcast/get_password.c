/*
** get_password.c for get_password in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May  5 13:15:42 2017 Arthur Knoepflin
** Last update Fri May  5 13:19:10 2017 Arthur Knoepflin
*/

#include <stdlib.h>

char	*get_password()
{
  int	i;
  char	*ret;

  if ((ret = malloc(sizeof(char) * 5)) == NULL)
    return (NULL);
  ret[4] = '\0';
  i = 0;
  while (i < 4)
    {
      ret[i] = (rand() % 10) + '0';
      i += 1;
    }
  return (ret);
}
