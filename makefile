# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/25 11:15:10 by ahammout          #+#    #+#              #
#    Updated: 2023/03/31 01:40:58 by ahammout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -fsanitize=address
CC = gcc  

#CFLAGS = -Wall -Wextra -Werror -g

READLINEFLAG =   -lreadline 

LIBFT = libft/libft.a

NEXTLINE = get_next_line/get_next_line.a

INCLUDES = includes/minishell.h

NAME = minishell

SRCS = 	srcs/main.c \
		srcs/parsing/tools.c \
		srcs/parsing/parse_line.c \
		srcs/parsing/lexer/lexer.c \
		srcs/parsing/lexer/lexer_check_tools.c \
		srcs/parsing/lexer/lexer_tools.c \
		srcs/parsing/lexer/lexer_quotes.c \
		srcs/parsing/environment/set_environment.c \
		srcs/parsing/environment/sort_environemnt.c \
		srcs/parsing/environment/set_env_tools.c \
		srcs/parsing/syntax_analyzer/syntax_analyzer.c \
		srcs/parsing/syntax_analyzer/syntax_analyzer_.c \
		srcs/parsing/syntax_analyzer/syntax_quotes.c \
		srcs/parsing/expander/expander.c \
		srcs/parsing/expander/expandable.c \
		srcs/parsing/expander/unexpandable.c \
		srcs/parsing/expander/expander_tools.c \
		srcs/parsing/parser/parser.c \
		srcs/parsing/parser/parser_tools.c \
		srcs/parsing/parser/redirections_handler.c \
		srcs/parsing/parser/heredoc_handler.c \
		srcs/execution/built_in_cmd.c \
		srcs/execution/export.c \
		srcs/execution/unset.c \
		srcs/execution/pipex.c \
		srcs/execution/pipex_extra.c \
		srcs/execution/pwd.c \
		srcs/execution/signal_handler.c \
		srcs/execution/exit.c \
		srcs/execution/cmd_exec.c \
		srcs/execution/echo.c \
		srcs/execution/cd.c \
		srcs/execution/core.c\

OBJS = $(SRCS:.c=.o)

%.o : %.c $(INCLUDES) -lreadline
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS) $(INCLUDES)
	@make -C libft
	@make -C get_next_line
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(NEXTLINE) $(READLINEFLAG)  -o $(NAME)

clean :
	@make clean -C libft
	@make clean -C get_next_line
	@rm -rf $(OBJS)

fclean : clean
	@make fclean -C libft
	@make fclean -C get_next_line
	@rm -rf $(NAME)

re : fclean all
