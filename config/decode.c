/*
** decode.c for decode in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed Apr 26 00:24:55 2017 Arthur Knoepflin
** Last update Thu Apr 27 18:20:15 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <ctype.h>
#include "server.h"

int	urldecode(char *sSource, char *sDest)
{
  int	nLength;

  nLength = 0;
  while (*sSource)
    {
      if (*sSource == '%' && sSource[1] && sSource[2] &&
	  isxdigit(sSource[1]) && isxdigit(sSource[2]))
	{
	  sSource[1] -= sSource[1] <= '9' ? '0' :
	    (sSource[1] <= 'F' ? 'A' : 'a') - 10;
	  sSource[2] -= sSource[2] <= '9' ? '0' :
	    (sSource[2] <= 'F' ? 'A' : 'a') - 10;
	  sDest[nLength] = 16 * sSource[1] + sSource[2];
	  sSource += 3;
	}
      else
	sDest[nLength] = *sSource++;
      nLength++;
    }
  sDest[nLength] = '\0';
  return (nLength);
}
