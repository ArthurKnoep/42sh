/*
** load_file.c for load_file in /home/arthur/delivery/COLLE/CPE_2016_stumper4
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 10 14:41:00 2017 Arthur Knoepflin
** Last update Fri May 12 22:42:59 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "get_next_line.h"
#include "my.h"

void	free_tab(char **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i])
    {
      free(tab[i]);
      i += 1;
    }
  free(tab);
}

int	nb_tab(char **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i])
    i += 1;
  return (i);
}

static char	**add_line(char **actual, char *line)
{
  int		i;
  char		**ret;

  if ((ret = malloc(sizeof(char *) * (nb_tab(actual) + 2))) == NULL)
    return (NULL);
  ret[nb_tab(actual) + 1] = NULL;
  i = 0;
  while (actual && actual[i])
    {
      ret[i] = my_strdup(actual[i]);
      free(actual[i]);
      i += 1;
    }
  ret[i] = line;
  free(actual);
  return (ret);
}

char	**load_file(int fd)
{
  char	*line;
  char	**ret;

  ret = NULL;
  while ((line = get_next_line(fd)))
    {
      if ((ret = add_line(ret, line)) == NULL)
	return (NULL);
    }
  return (ret);
}
