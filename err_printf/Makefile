# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 01:55:25 by aklaikel          #+#    #+#              #
#    Updated: 2022/02/28 03:43:38 by aklaikel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
INC = ft_printf.h
AR := ar rc
FLAGS = -Wall -Wextra -Werror
REMOVE := rm -rf
SRCS = ft_printf.c\
        ft_print_uhexa.c\
        ft_print_hexa.c\
        ft_printstr.c\
        ft_putchar_fd.c\
        ft_putnbr_fd.c\
        ft_putnbr_u_fd.c\
        ft_putstr_fd.c\
        ft_strlen.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(INC)
	@$(AR) $@ $^
%.o: %.c $(INC)
	@cc $(FLAGS) -c $< -o $@


clean:
	@$(REMOVE) $(OBJS)

fclean: clean
	@$(REMOVE) $(NAME)

re: fclean all
