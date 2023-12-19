# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 09:24:19 by ylachhab          #+#    #+#              #
#    Updated: 2023/04/01 13:10:20 by ylachhab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftgnl.a

FLAGS = -Wall -Wextra -Werror

CC = cc

AR = ar rc

RM = rm -f

SRC  = 	get_next_line.c \
		get_next_line_utils.c

OBJS = $(SRC:.c=.o)

all:  $(NAME)

%.o : %.c get_next_line.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all