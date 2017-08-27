/*
** split_it.c for split_it in /home/Maxime/delivery/PSU/PSU_2016_minishell2/Utility/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu Apr  6 09:36:47 2017 Maxime Jenny
** Last update	Fri May 19 09:56:13 2017 Full Name
*/

#include <stdlib.h>

int		is_in(char str, char *test)
{
  int		i;

  i = -1;
  while (test[++i] != '\0')
    {
      if (test[i] == str)
	return (1);
    }
  return (0);
}

static int	find_len(char *str, char *to_split)
{
  int	i;
  int	c;

  i = 0;
  c = 1;
  while (str[i])
    {
      if (is_in(str[i], to_split))
	c++;
      i++;
    }
  return (c + 1);
}

int	word_length(char *str, int i, char *to_split)
{
  int	c;

  c = 0;
  while (str[i + c] && !is_in(str[i + c], to_split))
    c++;
  return (c);
}

static char	**cut_it(char *str, char **tab, char *to_split)
{
  int	x;
  int	y;
  int	i;

  i = 0;
  y = 0;
  while (str[i])
    {
      x = 0;
      if (!is_in(str[i], to_split))
	{
	  if ((tab[y] = malloc(word_length(str, i, to_split) + 1)) == NULL)
	    return (NULL);
	  while (str[i] && !is_in(str[i], to_split))
	    tab[y][x++] = str[i++];
	  tab[y++][x] = '\0';
	}
      if (str[i])
	i++;
    }
  tab[y] = NULL;
  return (tab);
}

char	**split_it(char *str, char *to_split)
{
  char	**tab;

  if ((tab = malloc(sizeof(char *) * find_len(str, to_split))) == NULL)
    return (NULL);
  if ((tab = cut_it(str, tab, to_split)) == NULL)
    return (NULL);
  return (tab);
}
