/*
** my_strcat.c for my_strcat in /home/nicolas.polomack/CPool_Day07
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
**
** Started on  Tue Oct 11 10:30:59 2016 Nicolas POLOMACK
** Last update Mon Feb 20 23:27:07 2017 
*/

char	*my_strcat(char *dest, char *src)
{
  int	count;
  int	i;

  i = 0;
  count = 0;
  while (dest[count])
    count += 1;
  while (src[i])
    {
      dest[count] = src[i];
      i += 1;
      count += 1;
    }
  dest[count] = '\0';
  return (dest);
}
