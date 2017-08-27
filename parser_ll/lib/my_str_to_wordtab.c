/*
** my_str_to_wordtab.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 21:23:24 2017 Benjamin
** Last update Sun May 21 16:08:32 2017 Benjamin
*/

#include <stdlib.h>

static int	to_parse(char c, char *parse)
{
  int		j;

  j = -1;
  while (parse[++j] != '\0')
    {
      if (c == parse[j])
	{
	  return (0);
	}
    }
  return (1);
}

static int	count_wordtab(char *str, char *parse)
{
  int		i;
  int		count;

  i = 0;
  count = 0;
  while (str[i] != '\0')
    {
      if (to_parse(str[i], parse) == 1 && str[i] != '\0')
	{
	  count++;
	  while (to_parse(str[i], parse) == 1 && str[i] != '\0')
	    {
	      i++;
	    }
	}
      if (to_parse(str[i], parse) == 0 && str[i] != '\0')
	while (to_parse(str[i], parse) == 0 && str[i] != '\0')
	    {
	      i++;
	    }
    }
  return (count);
}

static int	count_str(char *str, char *parse, int i)
{
  int		mem;

  mem = 0;
  while (to_parse(str[i + mem], parse) == 1 && str[i + mem])
    mem++;
  return (mem);
}

char	**bs_str_to_wordtab(char *str, char *parse)
{
  char	**tab;
  int	ijkl[4];

  ijkl[0] = 0 + (ijkl[1] = 0) + (ijkl[3] = 0);
  if (!str || (!(tab = malloc(sizeof(char *) *
			      (count_wordtab(str, parse) + 1)))))
    return (NULL);
  while (ijkl[3]++ < count_wordtab(str, parse))
    {
      while (to_parse(str[ijkl[0]], parse) == 0 && str[ijkl[0]] != '\0')
	ijkl[0]++;
      ijkl[2] = 0;
      if (str[ijkl[0]] != '\0')
	{
	  if (!(tab[ijkl[1]] = malloc(sizeof(char) * (count_str(str, parse,
						      ijkl[0]) + 1))))
	    {
	    }
	  while (to_parse(str[ijkl[0]], parse) == 1 && str[ijkl[0]] != '\0')
	    tab[ijkl[1]][ijkl[2]++] = str[ijkl[0]++];
	  tab[ijkl[1]++][ijkl[2]] = '\0';
	}
    }
  tab[ijkl[1]] = NULL;
  return (tab);
}
