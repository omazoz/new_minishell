# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 14:40:41 by omazoz            #+#    #+#              #
#    Updated: 2022/06/06 22:25:41 by omazoz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = ${SRCS_MAIN} ${SRCS_UTILS} ${SRCS_PARSING} ${SRCS_LEXER} ${SRCS_LIBFT} \
		${SRCS_BUILTINS} ${SRCS_EXEC}

SRCS_MAIN = $(addprefix srcs/, main.c)

SRCS_UTILS = $(addprefix srcs/utils/, free/ft_free.c init.c error.c env.c\
				free/free_strs.c ft_malloc.c free/utils.c prompt.c ft_open.c \
				signals.c fd_error.c)

SRCS_PARSING = $(addprefix srcs/parsing/, first_check.c \
				first_check_redir.c parsing.c parsing_utils.c \
				cmd_utils.c scan_dollar.c scan_dollar_utils.c \
				find_bin_path.c scan_tokens_utils.c scan_tokens.c \
				del_whitespaces.c heredoc.c heredoc_utils.c \
				scan_dollar_utils2.c)

SRCS_LEXER = $(addprefix srcs/lexer/, lexer.c lexer_utils.c \
				char_to_token.c token_manager.c)

SRCS_LIBFT = $(addprefix srcs/libft/, ft_putstr_fd.c ft_strlen.c \
				ft_strncmp.c ft_substr.c ft_split.c ft_env_lst.c \
				ft_strdup.c ft_is_whitespace.c ft_strchr.c ft_isalpha.c \
				ft_isdigit.c ft_calloc.c ft_bzero.c ft_nsplit.c ft_strcmp.c \
				ft_strjoin.c ft_strjoin_char.c ft_strcdup.c ft_lstsize.c \
				ft_atoll.c ft_itoa.c ft_atoi.c)

SRCS_BUILTINS = $(addprefix srcs/builtins/, echo.c cd.c env.c export/export.c \
				export/check.c export/utils.c pwd.c unset.c exit.c \
				export/display.c)

SRCS_EXEC = $(addprefix srcs/exec/, exec.c exec_utils.c exec_return.c loop.c)

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = cc

CFLAGS := -Wall -Wextra -Werror

LFLAGS := -L/goinfre/omazoz/.brew/opt/readline/lib

IFLAGS := -I/goinfre/omazoz/.brew/opt/readline/include


RM = rm -f

all: ${NAME}

${NAME}: ${SRCS}
	${CC} ${CFLAGS} ${SRCS} -lreadline -lncurses $(LFLAGS) $(IFLAGS) -o ${NAME}
# ${CC} ${CFLAGS} ${SRCS} -l$(shell brew readline)/lib -lreadline -lncurses $(LFLAGS) $(IFLAGS) -o ${NAME}

# %.o:%.c $(HEADER)
# 	@${CC} $(CFLAGS) -I$(IFLAGS) -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

rc: fclean all
	${RM} ${OBJS} && clear

.PHONY: all clean fclean re
