##
## Makefile for Makefile in /home/nicolas/graphical/bootstrap_wireframe/
##
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
##
## Started on  Tue Nov 15 09:05:43 2016 Nicolas Polomack
## Last update Sun May 21 23:35:06 2017 Arthur Knoepflin
##

MAKE1	=	make -sC lib/my --no-print-directory

SRC	=	alias/alias.c				\
		alias/edit.c				\
		alias/loop.c				\
		alias/parse.c				\
		alias/unalias.c				\
		parse/bufferize.c			\
		builtins.c				\
		builtins_init.c				\
		builtins/alias.c			\
		builtins/cd.c				\
		builtins/char_double.c			\
		builtins/check_file.c			\
		builtins/check_file_2.c			\
		builtins/config.c			\
		builtins/dualcast.c			\
		builtins/echo.c				\
		builtins/env.c				\
		builtins/env_checkerr.c			\
		builtins/env_cherror_2.c		\
		builtins/exec_arg.c			\
		builtins/exec_arg_2.c			\
		builtins/exit.c				\
		builtins/launch_soft.c			\
		builtins/parse_env.c			\
		builtins/parserll.c			\
		builtins/prompt.c			\
		builtins/set.c				\
		builtins/setenv.c			\
		builtins/shw_env_parse.c		\
		builtins/show_signal.c			\
		builtins/unalias.c			\
		builtins/unset.c			\
		builtins/unsetenv.c			\
		builtins/where.c			\
		builtins/which.c			\
		cd.c					\
		comment.c				\
		config/add_env_http.c			\
		config/client.c				\
		config/com_serv.c			\
		config/config.c				\
		config/exec_cmd_http.c			\
		config/exit.c				\
		config/decode.c				\
		config/get_env.c			\
		config/get_info_pc.c			\
		config/get_file_http.c			\
		config/get_request.c			\
		config/init_connection.c		\
		config/int_toc.c			\
		config/my_split.c			\
		config/my_split_char.c			\
		config/my_split_mulchar.c		\
		config/navigator.c			\
		config/prompt.c				\
		config/response.c			\
		config/send_env.c			\
		config/send_info.c			\
		config/send_file_http.c			\
		config/send_mime.c			\
		echo.c					\
		env/env.c				\
		env/env2.c				\
		exec/exec.c				\
		exec/exec2.c				\
		exec/pipe.c				\
		exec/close.c				\
		exec/setup.c				\
		dualcast.c				\
		dualcast/com_sock.c			\
		dualcast/connect.c			\
		dualcast/core_server.c			\
		dualcast/core_client.c			\
		dualcast/get_password.c			\
		dualcast/init_dualcast.c		\
		dualcast/prompt_client.c		\
		dualcast/prompt_serv.c			\
		dualcast/termio.c			\
		dualcast/term_emul.c			\
		dualcast/response_serv.c		\
		dualcast/wait_connection.c		\
		launch_config.c				\
		free.c					\
		globbing/globbing.c			\
		globbing/history.c			\
		globbing/home.c				\
		globbing/stars.c			\
		history.c				\
		home.c					\
		magic/construct.c			\
		magic/magic.c				\
		misc.c					\
		parse/parse.c				\
		parse/error.c				\
		parser_ll/ast_arg.c			\
		parser_ll/ast_lvl_build_branch.c	\
		parser_ll/ast_lvl.c			\
		parser_ll/ast.c				\
		parser_ll/parse.c			\
		parser_ll/print_ast.c			\
		parser_ll/token.c			\
		parser_ll/set/arg.c			\
		parser_ll/set/op_high.c			\
		parser_ll/set/op_low.c			\
		parser_ll/set/redir.c			\
		parser_ll/lib/my_str_to_wordtab.c	\
		parser_ll/lib/my_strcat.c		\
		path/path.c				\
		path/path2.c				\
		print.c					\
		prompt.c				\
		prompt/bash.c				\
		prompt/turbosh.c			\
		prompt/tcsh.c				\
		prompt/minimalist.c			\
		prompt/ketchup.c			\
		prompt/bigmac.c				\
		prompt/oh_my_zsh.c			\
		prompt/mechanics/advanced.c		\
		prompt/mechanics/fct.c			\
		prompt/mechanics/tmp.c			\
		prompt/mechanics/load_file.c		\
		prompt/mechanics/prompt.c		\
		prompt/mechanics/actions.c		\
		prompt/mechanics/char.c			\
		prompt/mechanics/sauv.c			\
		prompt/mechanics/cursor.c		\
		prompt/mechanics/misc.c			\
		prompt/get_cur_branch.c			\
		vars.c					\
		my_sh.c					\
		exit.c					\
		parse/line.c				\
		redirects.c				\
		buffer.c				\
		char.c					\
		init.c					\
		is/is.c					\
		is/is2.c				\
		get_next_line.c				\
		auto_completation/auto_complete.c	\
		auto_completation/auto_list.c		\
		auto_completation/match.c		\
		auto_completation/split_it.c		\
		auto_completation/free_dirent.c		\
		auto_completation/auto_token.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Iinclude -Llib/my -lmy -lncurses -D_GNU_SOURCE=1 -W -Wall -Wextra -Werror -g

REDDARK	=	\033[31;2m

RED	=	\033[31;1m

GREEN	=	\033[32;1m

YEL	=	\033[33;1m

BLUE	=	\033[34;1m

PINK	=	\033[35;1m

CYAN	=	\033[36;1m

RES	=	\033[0m

NAME	=	42sh

all:	$(NAME)

$(NAME):$(OBJ)
	@echo
	@echo -e "$(GREEN)Everything compiled smoothly. Now compiling dependancies...$(RES)"
	@echo
	@echo -en "$(CYAN)Compiling libmy...$(RES)"
	@$(MAKE1)
	@echo -e "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo -en "$(CYAN)Linking TurboSh...$(RES)"
	@gcc -o $(NAME) $(OBJ) $(CFLAGS)
	@echo -e "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo
	@echo -e "$(GREEN)---- TURBOSH READY ----$(RES)"
	@echo

clean:
	@$(MAKE1) clean
	@$(foreach var, $(OBJ), if [ -e $(var) ] ; then \
	printf "[$(RED)RM$(RES)] $(YEL)$(var)$(RES)\n" \
	&& $(RM) $(var) ; fi ;)

fclean:	clean
	@$(MAKE1) fclean
	@if [ -e $(NAME) ] ; then \
	printf "[$(RED)RM EXEC$(RES)] $(YEL)$(NAME)$(RES)\n" \
	&& rm -f $(NAME) ; fi

re:	fclean all

%.o:	%.c
	@echo -e "[$(RED)COMPILE$(RES)] $(YEL)$<$(RES) $(BLUE)=>$(RES) $(YEL)$@$(RES)"
	@gcc $(CFLAGS) -o $@ -c $<
