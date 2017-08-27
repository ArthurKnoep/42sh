/*
** server.h for server in /home/arthur/test_sock/server
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Wed Dec 21 20:06:39 2016 Arthur Knoepflin
** Last update Thu May 18 13:07:33 2017 Arthur Knoepflin
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <termios.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# define	INVALID_SOCKET	-1
# define	SOCKET_ERROR	-1
# define	DUALCAST_PORT	33000
# define	SIZE_SOCK	4096
# define	closesocket(s)	close(s)
typedef int			t_socket;
typedef	struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr		t_sockaddr;
typedef struct in_addr		t_in_addr;

typedef struct	s_info_pc
{
  char		*plateforme;
  char		*version;
  char		*hostname;
  char		*os;
  int		mem_total;
  int		mem_available;
  char		*proco;
}		t_info_pc;

typedef struct	s_config
{
  char		**env;
  int		prompt;
}		t_config;

typedef struct	s_client
{
  t_socket	sock;
  int		len_prompt;
  char		*name;
}		t_client;

# define	MIMETYPE	"mimetype"
# define	CRLF		"\r\n"
# define	MAX_CLIENTS	100
# define	CHROME		"google-chrome"
# define	FIREFOX		"firefox"
# define	MAGIC		"exec"
# define	PATH_WEB	"http://localhost:"
# define	PATH_DOC	"config/WebC/"
# define	NF_RESP		"HTTP/1.0 404\r\n\
Access-Control-Allow-Origin: *\r\n\r\n\
<!DOCTYPE html><html><head><title>Configuration</title></head>\
<body><h1>404 Not found</h1>\
Le fichier n'existe po</body>\
</html>"
# define	FB_RESP		"HTTP/1.0 403\r\n\
Access-Control-Allow-Origin: *\r\n\r\n\
<!DOCTYPE html><html><head><title>Configuration</title></head>\
<body><h1>403 Forbiden Acess</h1>\
Ta pas les perms frere</body>\
</html>"
# define	ERROR_RESP	"HTTP/1.0 500\r\n\
Access-Control-Allow-Origin: *\r\n\r\n\
<!DOCTYPE html><html><head><title>Configuration</title></head>\
<body><h1>Internal server error</h1></body></html>"
# define	BASE_RESP	"HTTP/1.0 200\r\n\
Access-Control-Allow-Origin: *\r\n\
Content-type: text/plain\r\n\r\n"
# define	HEAD_RESP	"HTTP/1.0 200\r\n\
Access-Control-Allow-Origin: *\r\n"
# define	BUF_SIZE	4096

/*
** add_env_http.c
*/

void	add_env_http(t_socket, t_config *, char **);
void	del_env_http(t_socket, t_config *, char **);
void	update_env_http(t_socket, t_config *, char **);

/*
** char_double.c
*/

char	**add_to_chardouble(char *, char **);
char	**del_to_chardouble(char *, char **);

/*
** client.c
*/

void	remove_client(t_socket *, int, int *);
int	new_client(t_socket *, int *, fd_set *, t_socket);
int	client_talk(t_socket *, int *, fd_set *, t_config *);

/*
** com_serv.c
*/

int	read_client(t_socket, char *);
void	write_client(t_socket, char *);

/*
** decode.c
*/

int	urldecode(char *, char *);

/*
** exec_cmd_http.c
*/

void	exec_cmd_http(t_socket, t_config *, char **);

/*
** exit.c
*/

void	exit_config(t_socket, t_config *, char **);

/*
** init_connection.c
*/

int	init_connection(t_socket *);

/*
** indexof.c
*/

int	indexof(char **, char *);

/*
** int_toc.c
*/

char	*int_toc(int);

/*
** get_env.c
*/

char	*get_env(char *);

/*
** get_info.c
*/

t_info_pc	*get_info();

/*
** get_file_http.c
*/

char	*get_file_http(char *);

/*
** get_request.c
*/

int	nb_request();
int	indexof_request(char *);
void	get_tab_request(void (**)(t_socket, t_config *, char **));

/*
** my_split.c
*/

char	**my_split(char *, char *);

/*
** my_split_char.c
*/

char	**my_split_char(char *, char);

/*
** my_split_mulchar.c
*/

char	**my_split_mulchar(char *, char *);

/*
** navigator.c
*/

char	*find_navigator(char **);
int	launch_nav(char *, int, char **);

/*
** prompt.c
*/

void	send_prompt_sel(t_socket, t_config *, char **);
void	update_prompt_sel(t_socket, t_config *, char **);

/*
** response.c
*/

int	response(t_socket, char *, t_config *);

/*
** send_env.c
*/

void	send_env(t_socket, t_config *, char **);

/*
** send_info.c
*/

void	send_info(t_socket, t_config *, char **);

/*
** send_file_http.c
*/

void	send_file_http(t_socket, char *);

/*
** send_mime.c
*/

void	send_mime(t_socket, char *);

/*
** DUALCAST
*/

/*
** connect.c
*/

t_socket	init_connect_dc(char *, t_client *);

/*
** core_client.c
*/

int	core_client_dc(t_client *);

/*
** core_server.c
*/

int	core_server_dc(t_socket, t_socket, fd_set *);

/*
** com_sock.c
*/

int	read_socket(t_socket, char **);
void	write_socket(t_socket, char *);

/*
** prompt_client.c
*/

char	*get_prompt_cli(t_client *);

/*
** prompt_serv.c
*/

void	prompt_serv(t_socket, char, char **, int *);

/*
** response_serv.c
*/

int	response_serv(t_socket, char *, char **, int *);

/*
** termio.c
*/

void	reset_terminal_mode(struct termios *);
void	set_conio_terminal_mode(struct termios *);
int	kbhit();
int	getch_c();

/*
** term_emul.c
*/

void	del_last_char(int, char **, int *);
void	add_char_dc(char **, char, int *);
void	del_prompt(int);
void	send_char(t_socket, char);

#endif /* !SERVER_H_ */
