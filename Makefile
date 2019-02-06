# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apeyret <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/10 18:24:48 by apeyret           #+#    #+#              #
#    Updated: 2019/02/04 14:50:26 by ktlili           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh 

CC = gcc

CFLAGS = -I inc/ -I lib/ -Wall -Werror -Wextra -g

DEBUG= #-g3 -fsanitize=address

INC_DIR = inc

INC_FILE =	ft_eval.h \
			ft_lexer.h \
			ft_readline.h \
			ft_wordexp.h \
			sh_core.h

SRC_DIR = src

SRC_FILE =	core/builtins.c \
			core/cd_l_p.c \
			core/cd_tools.c \
			core/changedir.c \
			core/clean_path.c \
			core/dynamic_buff.c \
			core/env_handler.c \
			core/env_lst_util.c \
			core/env_lst_util2.c \
			core/ft_env.c \
			core/ft_env_tools.c \
			core/main.c \
			core/path_tools.c \
			core/util.c \
			core/util2.c \
			eval/expansion_wrappers.c \
			eval/eval_pipe.c \
			eval/bin_path.c \
			eval/eval.c \
			eval/spawn_bin.c \
			eval/craft_env.c \
			eval/handle_redir.c \
			ft_wordexp/expansion_util.c \
			ft_wordexp/field_split.c \
			ft_wordexp/ft_wordexp.c \
			ft_wordexp/param_expand.c \
			ft_wordexp/quote_removal.c \
			ft_wordexp/tilde_expand.c \
			lexer/ft_realloc.c \
			lexer/lex_jump_table.c \
			lexer/lexer.c \
			lexer/lexer_tools.c \
			lexer/memerror.c \
			parser/parser_ast.c \
			parser/parser_rules.c \
			parser/parser_test.c \
			parser/parser_tools.c \
			parser/sh_parser.c

OBJ_DIR = .obj
OBJ_FILE = $(SRC_FILE:.c=.o)

CRT_DIR = core \
		  ft_wordexp \
		  lexer \
		  eval \
		  parser

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILE))
INC = $(addprefix $(INC_DIR)/,$(INC_FILE))
OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_FILE))
CRT = $(addprefix $(OBJ_DIR)/,$(CRT_DIR))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile
	@printf "\033[0;32m[21sh] Compilation [o.]\033[0;0m\r"
	@mkdir -p $(CRT) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32m[21sh] Compilation [.o]\033[0;0m\r"

norm:
	@norminette $(SRC)
	@norminette $(INC)

$(NAME): $(OBJ)
	@printf "\033[0;32m[21sh] Compilation [OK]\033[0;0m\n"
	@make -C lib/
	@gcc $(CFLAGS) $(DEBUG) $(OBJ) lib/libft.a -o $(NAME)

clean:
	@make clean -C lib/
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf $(OBJ_DIR)
	@printf "\033[0;31m[21sh] Deleted *.o\033[0;0m\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@printf "\033[0;31D[21sh] Deleted minishell\033[0;0m\n"

re: fclean all

.PHONY: all clean fclean re
