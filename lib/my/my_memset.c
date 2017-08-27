/*
** my_memset.c for my_memset in /home/arthur/delivery/PSU/PSU_2016_tetris
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Feb 25 12:05:34 2017 Arthur Knoepflin
** Last update Sat Feb 25 12:29:19 2017 Arthur Knoepflin
*/

void	*my_memset(void *str, int c, int size)
{
  char	*tmp;

  if (size)
    {
      size += 1;
      tmp = str;
      while (--size)
	{
	  *tmp++ = c;
	}
    }
  return (str);
}
