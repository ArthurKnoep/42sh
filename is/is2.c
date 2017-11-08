/*
** is2.c for minishell2 in /home/nicolaspolomack/shell2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat Mar 25 20:21:25 2017 Nicolas Polomack
** Last update Sun Jul 30 04:32:00 2017 nicolaspolomack
*/

int	is_separator(char c)
{
  return (c == '>' || c == '<' || c == '|' || c == ';' || c == '&');
}

int	is_space(char c)
{
  return (c == ' ' || c == '\t');
}

int	is_delimiter(char c)
{
  return (c == ';' || c == '|');
}

int	is_alphanum(char c)
{
  return ((c >= 'a' && c <= 'z') ||
	  (c >= 'A' && c <= 'Z') ||
	  (c >= '0' && c <= '9') ||
	  c == '_');
}

int	is_num(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] < '0' || str[i] > '9')
	return (0);
      i += 1;
    }
  return (1);
}
