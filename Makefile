# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alramire <alramire@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 11:33:51 by alramire          #+#    #+#              #
#    Updated: 2024/09/14 17:04:27 by alramire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
SRC = main.c get_next_line.c get_next_line_utils.c utils.c boot_fdf.c ft_split.c map.c atoi.c init_mlx.c isometric.c bresenham.c
OBJ = $(SRC:.c=.o)
NAME = fdf

# Rules
all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJ)

fclean: clean
# @$(MAKE) -C $(MLX_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re




#NAME = fdf
#
#CC = gcc -g
#
#FLAGS = -Wall -Wextra -Werror
#
#INCLUDE = -I./include -Lminilibx-linux -lX11 -lXext -lmlx
#
#SRCS = get_next_line_utils.c get_next_line.c main.c
#
#
#OBJS = $(SRCS:.c=.o)
#
#RM = rm -f
#
#all: $(NAME)
#
#$(NAME): $(OBJS)
#	@make -C minilibx
#	$(CC) $(FLAGS) $(INCLUDE) -o $(NAME) $(OBJS)
#
#%.o: %.c
#	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
#
#minilibx:
#		make -C minilibx
#
#clean:
#	$(RM) $(OBJS)
#	make clean -C minilibx
#
#fclean: clean
#	$(RM) $(NAME)
#
#re: fclean all
#
#.PHONY: all clean fclean re
#
