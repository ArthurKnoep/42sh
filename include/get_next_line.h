/*
** get_next_line.h for get_next_line in /home/nicolaspolomack/cpe/CPE_2016_getnextline
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Jan  2 12:57:44 2017 Nicolas Polomack
** Last update Sun May 21 11:40:32 2017 Arthur Knoepflin
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

#ifndef READ_SIZE
# define READ_SIZE 10
#endif /* !READ_SIZE */

char	*get_next_line(const int);
int	get_line_str(const int, char **, int);
char	*get_final_line(char **);
char	*my_realloc(char *, char *);
char	*line_cases(int, int *, char **);

#endif /* !GET_NEXT_LINE_H_ */
