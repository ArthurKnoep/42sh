/*
** termio.c for termio in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon May  8 17:15:38 2017 Arthur Knoepflin
** Last update Thu Jun  1 14:09:21 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include "server.h"

void	reset_terminal_mode(struct termios *orig_termios)
{
  tcsetattr(0, TCSANOW, orig_termios);
}

void			set_conio_terminal_mode(struct termios *orig_termios)
{
  struct termios	new_termios;

  tcgetattr(0, orig_termios);
  memcpy(&new_termios, orig_termios, sizeof(new_termios));
  cfmakeraw(&new_termios);
  tcsetattr(0, TCSANOW, &new_termios);
}

int			kbhit()
{
  struct timeval	tv;
  fd_set		fds;

  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(0, &fds);
  return (select(1, &fds, NULL, NULL, &tv));
}

int		getch_c()
{
  int		r;
  unsigned char	c;

  if ((r = read(0, &c, sizeof(c))) < 0)
    return (r);
  else
    return (c);
}
