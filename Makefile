# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/17 12:12:22 by nlaurids          #+#    #+#              #
#    Updated: 2021/10/05 17:56:44 by nlaurids         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS_NAME	= bitmap.c get_next_line.c key.c movement.c main.c mlx_main.c \
	   parse_sres.c parse_tex.c parse_fc.c parse_map.c parse_map0.c \
	   raycast.c raycast0.c split.c sprite.c utils.c utils0.c utils1.c utils2.c

INC_NANE	= cub3d.h get_next_line.h

SRCS		= $(addprefix srcs/, $(SRCS_NAME))

INC			= $(addprefix srcs/, $(INC_NAME))

OBJS		= $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
EXTRAFLAGS = -Lminilibx -lmlx -framework AppKit -framework OpenGL

all:		$(NAME)

$(NAME):	$(OBJS) $(INC)
			$(CC) $(CFLAGS) $(EXTRAFLAGS) $(OBJS) -o $(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME) screenshot.bmp

re:			fclean all

.PHONY =	all clean fclean re
