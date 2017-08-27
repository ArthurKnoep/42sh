/*
** my_puterror.c for my_puterror in /home/arthur/delivery/CPE/CPE_2016_corewar/corewar
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Thu Mar  9 22:26:15 2017 Arthur Knoepflin
** Last update Thu Mar  9 22:30:04 2017 Arthur Knoepflin
*/

#include <unistd.h>

int	my_puterror(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      write(2, &str[i], 1);
      i += 1;
    }
  return (i);
}
