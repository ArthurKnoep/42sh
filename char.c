/*
** char.c for minishell2 in /home/nicolaspolomack/psu/2/PSU_2016_minishell2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar 23 10:29:41 2017 Nicolas Polomack
** Last update Fri May  5 06:27:08 2017 Nicolas Polomack
*/

#include <stdlib.h>

void	insert_char(char **str, char c)
{
  int	i;
  char	*new;

  i = -1;
  if (*str == NULL)
    i = 0;
  else
    while ((*str)[++i]);
  if ((new = malloc(i + 2)) == NULL)
    return ;
  i = (*str == NULL) ? 0 : -1;
  if (*str != NULL)
    while ((*str)[++i])
      new[i] = (*str)[i];
  new[i++] = c;
  new[i] = 0;
  free(*str);
  *str = new;
}

void	insert_int(int **str, int c)
{
  int	i;
  int	*new;

  i = -1;
  if (*str == NULL)
    i = 0;
  else
    while ((*str)[++i]);
  if ((new = malloc(sizeof(int) * (i + 2))) == NULL)
    return ;
  i = (*str == NULL) ? 0 : -1;
  if (*str != NULL)
    while ((*str)[++i])
      new[i] = (*str)[i];
  new[i++] = c;
  new[i] = 0;
  free(*str);
  *str = new;
}
