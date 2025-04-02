# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 13:14:15 by jtuomi            #+#    #+#              #
#    Updated: 2025/04/02 11:12:12 by jrimpila         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AR = ar rcs
CC = cc
INCLUDE_DIRS = libft
CFLAGS = -Wall -Wextra -Werror -g3 -DUSER=\"$(USER)\" -gdwarf -fsanitize=address -fsanitize=undefined

SRC = lexer.c	ft_xcalloc.c parsing_utils.c heredocs.c init_utils.c\
	exit.c	env.c utils.c page.c rem_quotes.c open.c signal.c \
	main.c create_list.c ft_lstaddback.c input.c export.c redir.c \
	redirect.c exec.c path.c inbuild.c ft_atol_spec.c exp_utils.c \
	unset.c export_print.c echo.c ch_dir.c rem_quotes_utils.c
SRC := $(addprefix srcs/, $(SRC))
OBJ := $(SRC:%.c=%.o)
MAKE = make -C
NAME = minishell
LIBFT = ./libft/libft.a

all: $(NAME)
$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(DEBUG_OBJ) -L $(INCLUDE_DIRS) -lft -lreadline
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
$(LIBFT):
	$(MAKE) libft all supp
clean:
	$(MAKE) libft clean
	rm -f $(OBJ)
fclean: clean
	$(MAKE) libft fclean
	rm -f $(NAME)
re: fclean all
.PHONY:
	all, libft, clean, fclean, re
