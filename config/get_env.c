/*
** get_env.c for get_env in /home/arthur/delivery/PSU/PSU_2016_minishell1
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Wed Jan  4 14:16:49 2017 Arthur Knoepflin
** Last update Fri May  5 02:15:25 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "server.h"
#include "my.h"

char	*get_env(char *str)
{
  return (getenv(str));
}
