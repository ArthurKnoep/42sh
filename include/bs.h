/*
** bs.h for lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:17:22 2017 Benjamin
** Last update Sun May 21 15:57:55 2017 Benjamin
*/

#ifndef BS_H_
# define BS_H_

#include "stdio.h"

int	cnt_str_char(char *str, char c);
int	cnt_line_tab(char **tab);

int	is_alpha(char c);
int	is_alphanum(char c);
int	is_lower(char c);
int	my_isneg(int n);
int	is_num(char c);
int	is_prime(int nb);
int	is_printable(char c);
int	is_str_anum(char *str);
int	is_str_char(char *str, char c);
int	is_str_num(char *str);
int	is_upper(char c);

void	my_free_tab(char **tab);

char	*my_concat(char *str, char *str2);
char	**my_cpy_tab(char **to_cpy);
char	*my_epur_str(char *str);
int	my_find_prime_sup(int nb);
int	my_getnbr(char *str);
void	*my_memset(void *toset, int tobeset, size_t size);
int	my_power_rec(int nb, int p);
void	my_put_error(char *str);
void	my_convertnbr_base_rec(int nbr, char* base, int base_len, char* str);
void	my_putnbr_base(int nb, char *base);
void	my_putptr_base(void* ptr, char* base);
void	my_put_nbr(int nb);
void	my_putchar(char c);
int	my_putstr(char *str);
char	*my_revstr(char *str);
void	my_show_tab(char **tab);
void	my_showmem(char *str, int size);
void	my_showstr(char *str);
void	my_sort_int_tab(int* tab, int size);
void	my_sort_wordtab(char **tab);
int	my_square_root(int nb);
char	**bs_str_to_wordtab(char *str, char *to_parse);
char	*my_strcapitalize(char *str);
char	*bs_strcat(char *dest, char *src);
int	my_strcmp(char *s1, char *s2);
char	*my_strcpy(char *dest, char *src);
char	*my_strdup(char *str);
int	my_strlen(char *str);
char	*my_strlowcase(char *str);
char	*my_strncat(char *dest, char *src, int nb);
int	my_strncmp(char *s1, char *s2, int n);
char	*my_strncpy(char *dest, char *src, int n);
char	*my_strstr(char *str, char *to_find);
char	*my_strupcase(char *str);
int	my_swap(int *a, int *b);

#endif /* !BS_H_ */
