# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heynard <heynard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/08 15:38:42 by heynard           #+#    #+#              #
#    Updated: 2017/06/27 20:26:37 by heynard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc

FLAGS = -Wall -Wextra -Werror -ltermcap

FLAGS_LFT = -L ./libft/ -lft

PATH_SRCS_EDIT = ./srcs/line_editing/

PATH_SRCS_ENV = ./srcs/handle_env/

PATH_SRCS_SHELL = ./srcs/shell/

PATH_SRCS_LEXER = ./srcs/lexer/

PATH_SRCS_PARSER = ./srcs/parser/

PATH_SRCS_EXECS = ./srcs/execs/

PATH_SRCS_BUILTINS = ./srcs/builtins/

PATH_SRCS = ./srcs/

SRC_SHELL =	main.c\
			sh_call_shell.c\
			sh_handle_line.c\
			sh_error.c\
			signal_functions.c\
			sh_key_event.c\
			sh_alternative_shell.c\
			ft_shell.c\
 			sh_create_string.c\
			tools.c

SRC_LEXER = lexer.c\
			lexer_handler.c\
			lexer_handler2.c\
			lexer_handler3.c\
			lexer_handler4.c\
			sh_sub_dollar.c

SRC_PARSER = sh_parser.c\
			sh_parser_tools.c\
			sh_create_node_ast.c\
			sh_parser_word.c\
			sh_parser_redirection.c\
			sh_parser_operator.c\
			sh_parsing_if.c

SRC_EXECS = exec_tree.c\
			heredoc.c\
			heredoc2.c\
			sh_pipe.c\
			sh_exec_tools.c\
			sh_pathfinding.c\
			sh_redirections.c\
			sh_redirections2.c\
			sh_is_builtin.c

SRC_BUILTINS = sh_builtin_echo.c\
				sh_builtin_exit.c\
				sh_builtin_env.c\
				sh_builtin_setenv.c\
				sh_builtin_unsetenv.c\
				sh_builtin_cd.c\
				sh_builtin_cd_func.c

SRC_EDIT = sh_prompt.c\
			sh_window_param.c\
			sh_init_line.c\
			sh_string_functions.c\
			sh_move_cursor.c\
			sh_line_func.c\
			sh_find_word.c\
			sh_histo_func.c\
			sh_histo_func2.c\
			sh_select_func.c\
			sh_copy.c\
			sh_paste.c\
			sh_quote.c\
			sh_delete_char.c\
			sh_quotes2.c

SRC_ENV = sh_copy_environ.c\
			sh_init_env.c\
			sh_update_env.c\

SRCS_ENV = $(addprefix $(PATH_SRCS_ENV), $(SRC_ENV))
SRCS_EDIT = $(addprefix $(PATH_SRCS_EDIT), $(SRC_EDIT))
SRCS_SHELL = $(addprefix $(PATH_SRCS_SHELL), $(SRC_SHELL))
SRCS_LEXER = $(addprefix $(PATH_SRCS_LEXER), $(SRC_LEXER))
SRCS_PARSER = $(addprefix $(PATH_SRCS_PARSER), $(SRC_PARSER))
SRCS_EXECS = $(addprefix $(PATH_SRCS_EXECS), $(SRC_EXECS))
SRCS_BUILTINS = $(addprefix $(PATH_SRCS_BUILTINS), $(SRC_BUILTINS))

OBJ_ENV = $(SRCS_ENV:.c=.o)
OBJ_EDIT = $(SRCS_EDIT:.c=.o)
OBJ_SHELL = $(SRCS_SHELL:.c=.o)
OBJ_LEXER  = $(SRCS_LEXER:.c=.o)
OBJ_PARSER = $(SRCS_PARSER:.c=.o)
OBJ_EXECS = $(SRCS_EXECS:.c=.o)
OBJ_BUILTINS = $(SRCS_BUILTINS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_ENV) $(OBJ_EDIT) $(OBJ_SHELL) $(OBJ_LEXER) $(OBJ_PARSER) $(OBJ_EXECS) $(OBJ_BUILTINS)
	@make -C ./libft/
	@$(CC) $(FLAGS) $(FLAGS_LFT) $^ -o $(NAME)
	@echo "\033[1;34m21sh\t\t\033[1;33mBuilding\t\t\033[0;32m[OK]\033[0m"

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: all clean fclean re

clean:
	@make -C ./libft/ clean
	@rm -f $(OBJ_ENV) $(OBJ_EDIT) $(OBJ_SHELL) $(OBJ_LEXER) $(OBJ_PARSER) $(OBJ_EXECS) $(OBJ_BUILTINS)
	@echo "\033[1;34m21sh\t\t\033[1;33mCleaning objects\t\033[0;32m[OK]\033[0m"

fclean: clean
	@make -C ./libft/ fclean
	@rm -f $(NAME) $(OBJ_ENV) $(OBJ_EDIT) $(OBJ_SHELL) $(OBJ_LEXER) $(OBJ_PARSER) $(OBJ_EXECS) $(OBJ_BUILTINS)
	@echo "\033[1;34m21sh\t\t\033[1;33mCleaning 21sh\t\t\033[0;32m[OK]\033[0m"

re: fclean all
