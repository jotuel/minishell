# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 10:10:39 by jtuomi            #+#    #+#              #
#    Updated: 2025/04/01 15:57:27 by jrimpila         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
SRCS = ft_atof.c \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c\
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_ltostr.c
BONUS_SRCS = 	ft_lstadd_front_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstmap_bonus.c \
	ft_lstnew_bonus.c \
	ft_lstsize_bonus.c
SUPP_SRCS = ft_abs.c \
	ft_ldiv.c \
	ft_ltostr.c \
	ft_printf.c \
	specifiers.c
OBJS := $(SRCS:%.c=%.o)
BONUS_OBJS := $(BONUS_SRCS:%.c=%.o)
SUPP_OBJS := $(SUPP_SRCS:%.c=%.o)
OBJS_ALL := $(OBJS) $(BONUS_OBJS) $(SUPP_OBJS)
INC_DIR = .
CFLAGS = -Wall -Wextra -Werror -ggdb3 -gdwarf -fsanitize=address -fsanitize=undefined
CPPFLAGS = -I$(INC_DIR)
NAME = libft.a
AR = ar rcs $(NAME)
all: $(NAME)
$(NAME) : $(OBJS)
	$(AR) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
clean:
	rm -f $(OBJS_ALL)
fclean: clean
	rm -f $(NAME)
re: fclean all

bonus: $(BONUS_OBJS)
	$(AR) $(BONUS_OBJS)
supp: $(SUPP_OBJS)
	$(AR) $(SUPP_OBJS)

.PHONY: all clean fclean re bonus supp
