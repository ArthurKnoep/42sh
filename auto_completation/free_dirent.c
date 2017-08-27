/*
** free_dirent.c for free_dirent.c in /home/Maxime/delivery/PSU/PSU_2016_42sh/auto_completation/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Fri May 12 13:47:45 2017 Maxime Jenny
** Last update	Fri May 12 13:50:37 2017 Full Name
*/

#include <stdlib.h>
#include <dirent.h>

void		my_free_tab(void **tab)
{
  int		i;

  i = 0;
  while (tab[i])
    free(tab[i++]);
  free(tab);
}

void		my_free_dirent(struct dirent **tab, int size)
{
  int		i;

  i = 0;
  while (i < size)
    free(tab[i++]);
  free(tab);
}
