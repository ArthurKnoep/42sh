/*
** is_a_num.c for is_a_num in /home/arthur/delivery/PSU/PSU_2016_tetris
** 
** Made by 
** Login   <arthur@epitech.net>
** 
** Started on  Tue Feb 21 15:02:09 2017 
** Last update Tue Feb 21 15:04:04 2017 
*/

int	is_a_num(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] < '0' || str[i] > '9')
	return (0);
      i += 1;
    }
  return (1);
}
