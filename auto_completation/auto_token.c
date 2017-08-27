/*
** auto_token.c for auto_token in /home/Maxime/delivery/PSU/PSU_2016_42sh/auto_completation/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Fri May 12 13:59:20 2017 Maxime Jenny
** Last update	Tue May 16 15:57:33 2017 Full Name
*/

#include <stdlib.h>
#include "auto_complete.h"
#include "shell.h"
#include "my.h"

int		find_a_path(char **path, t_auto *token)
{
  int		i;
  char		*str;
  char		*new;

  str = token->token;
  i = my_strlen(str) - 1;
  while (i >= 0 && str[i] != '/')
    i--;
  if (i == 0 && str[i] != '/')
    return (0);
  else if (i >= 0)
    {
      if ((new = malloc(my_strlen((str + i)) + 1)) == NULL)
	return (-1);
      new = my_strdup(str + i + 1);
      token->token = new;
      *path = my_strndup(str, i + 1);
      token->pre_token = my_strcatdup(token->pre_token,
				      my_strndup(str, i + 1));
      free(str);
      token->is_path = 1;
    }
  return (1);
}

char		*extract_posttoken(char *str, int end)
{
  char		*post_token;
  int		i;
  int		m;

  i = end + 1;
  m = 0;
  if (end == 0)
    return (my_strdup(""));
  if (!str[end + 1])
    return (my_strdup(""));
  if ((post_token = malloc(my_strlen(str) - end)) == NULL)
    return (NULL);
  while (str[i])
    post_token[m++] = str[i++];
  post_token[m] = 0;
  return (post_token);
}

char		*extract_pretoken(char *str, int start)
{
  char		*pre_token;
  int		i;

  i = 0;
  if (start == 0)
    return (my_strdup(""));
  if ((pre_token = malloc(start + 1)) == NULL)
    return (NULL);
  while (i < start)
    {
      pre_token[i] = str[i];
      i++;
    }
  pre_token[i] = 0;
  return (pre_token);
}

char		*extract_token(char *str, int i, int *start, int *end)
{
  char		*token;
  int		m;

  if (str == NULL)
    return (my_strdup(""));
  while (i >= 0 && str && str[i] != ' ')
    i--;
  *start = ++i;
  *end = i + word_length(str, i, " ") - 1;
  if ((token = malloc(*end - *start + 2)) == NULL)
    return (NULL);
  m = 0;
  while (i <= *end)
    token[m++] = str[i++];
  token[m] = 0;
  return (token);
}

int		find_token(t_shell *shell, t_auto *token)
{
  int		start;
  int		end;

	start = 0;
	end = 0;
  if (!(token->token = extract_token(shell->line, shell->w.cur, &start, &end)))
    return (-1);
  if (!(token->pre_token = extract_pretoken(shell->line, start)))
    return (-1);
  if (!(token->post_token = extract_posttoken(shell->line, end)))
    return (-1);
  return (0);
}
