# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thitran <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/20 09:06:14 by thitran           #+#    #+#              #
#    Updated: 2025/04/01 13:34:34 by ibyeo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = lexer1.c lexer2.c lexer3.c lexer4.c lexer5.c lexer6.c lexer7.c lexer8.c parser.c  \
builtins1.c builtins2.c builtins3.c builtins4.c builtins5.c builtins6.c dollarquestion1.c dollarquestion2.c pipes1.c pipes2.c pipes3.c pipes4.c pipes5.c  \
redirections1.c redirections2.c heredoc.c environment1.c environment2.c executor1.c executor2.c executor3.c executor4.c executor5.c main.c \


Header = minishell.h

CFLAGS = -Wall -Wextra -Werror -g

READLINE = -lreadline -lncurses

LIBFT = ./libft
LIBFT_A = $(LIBFT)/libft.a

NAME = minishell

CC = cc

OBJ = ${SRC:.c=.o}

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	make -C $(LIBFT)

$(NAME): $(Header) $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) -o $(NAME) $(READLINE)

%.o: %.c $(Header)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

norm:
	norminette

succes:
	make re && ./minishell

.PHONY: all clean fclean re norm succes
