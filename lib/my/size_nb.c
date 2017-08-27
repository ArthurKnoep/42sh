/*
** size_nb.c for size_nb in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May 19 00:23:33 2017 Arthur Knoepflin
** Last update Fri May 19 00:26:11 2017 Arthur Knoepflin
*/

int	size_nb(int nb)
{
  int	i;

  i = 1;
  while ((nb /= 10))
    i += 1;
  return (i);
}
