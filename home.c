/*
** home.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 11:04:03 2017 Nicolas Polomack
** Last update Sun May 21 04:23:06 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

char	*detect_home(char *temp, char *home)
{
  int	i;
  int	j;

  i = 0;
  if (home != NULL)
    {
      while (temp[i] == home[i] && temp[i] != 0)
        i += 1;
      if (home[i] == 0)
        {
          temp[0] = '~';
          i -= (home[i - 1] == '/');
          j = 1;
          while (temp[i] != 0)
            {
              temp[j] = temp[i];
              i += 1;
              j += 1;
            }
          temp[j] = 0;
        }
    }
  return (temp);
}

char	*get_current(char *current, char *home)
{
  char	*temp;

  if ((temp = malloc(512)) == NULL)
    return (NULL);
  temp[0] = 0;
  current[0] = 0;
  if ((temp = getcwd(temp, 256)) == NULL)
    return (NULL);
  if (home && my_strcmp(home, "/"))
  temp = detect_home(temp, home);
  current = my_strcat(current, temp);
  free(temp);
  return (current);
}
