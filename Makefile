#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avolgin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/09 18:42:23 by avolgin           #+#    #+#              #
#    Updated: 2018/03/20 16:04:17 by avolgin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fdf

SRC_FDF =./fdf.c \
		./math/ft_fabs.c \
		./ft_rgb_convert.c \
		./read.c \
		./bresenhaim.c \
		./draw.c \
		./projection.c \
		./check.c \
		./free_list.c \
		./get_colour.c
OBJECT_FDF = $(SRC_FDF:.c=.o)

FLAGS = -Wall -Wextra

INCLUDES_MLX = -I /usr/local/include

LIBFT = ./libft2.0/libftprintf.a

MLX_LIB = -L /usr/local/lib/

FRAMEWORK = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME) : $(OBJECT_FDF)
		make -C ./libft2.0 re
		gcc -g -o $(NAME) $(FLAGS) $(INCLUDES_MLX) $(OBJECT_FDF) $(LIBFT) \
		$(MLX_LIB) $(FRAMEWORK)
%.o: %.c
		gcc -g $(FLAGS) -o $@ -c $<
clean:
		make -C ./libft2.0 clean
		/bin/rm -f $(OBJECT_FDF)
fclean: clean
		/bin/rm -f ./libft2.0/libftprintf.a
		/bin/rm -f $(NAME)
re:		fclean all tags

tags:
		rm -f TAGS
		etags -R *.c *.h
