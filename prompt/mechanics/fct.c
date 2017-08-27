/*
** fct.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue May 16 18:50:40 2017 Nicolas Polomack
** Last update Tue May 16 19:15:42 2017 Nicolas Polomack
*/

#include "shell.h"

void	get_cur_fcts(void (*cur_fct[6])(t_shell *))
{
  cur_fct[0] = move_backw;
  cur_fct[1] = move_forw;
  cur_fct[2] = move_upw;
  cur_fct[3] = move_downw;
  cur_fct[4] = move_home;
  cur_fct[5] = move_end;
}
