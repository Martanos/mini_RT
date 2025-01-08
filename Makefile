# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 14:14:50 by malee             #+#    #+#              #
#    Updated: 2025/01/08 14:08:49 by seayeo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini_rt

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g

SRC_DIR		= srcs/
OBJ_DIR		= obj/
LIBFT_DIR	= libft/
MLX_DIR		= minilibx-linux/

LIBFT		= $(LIBFT_DIR)libft.a
MLX			= $(MLX_DIR)libmlx.a

INCLUDES	= -I./include -I./$(LIBFT_DIR)includes -I./$(MLX_DIR)

MAIN_DIR	= 01_main/
UTILS_DIR	= UTILS/
RENDERPLANE_DIR	= renderplane/

MAIN_SRC	=	main.c
UTILS_SRC	=	misc.c vector_utils.c
RENDERPLANE_SRC	=	renderplane.c tracing.c check_sphere.c check_plane.c \
					check_cylinder.c

SRCS		= $(addprefix $(SRC_DIR)$(MAIN_DIR), $(MAIN_SRC)) \
			  $(addprefix $(SRC_DIR)$(UTILS_DIR), $(UTILS_SRC)) \
			  $(addprefix $(SRC_DIR)$(RENDERPLANE_DIR), $(RENDERPLANE_SRC))

OBJ_DIRS	= $(MAIN_DIR) $(UTILS_DIR) $(RENDERPLANE_DIR)
OBJS		= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# MLX Dependencies
MLX_FLAGS	= -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): create_dirs $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(MLX) $(MLX_FLAGS)

create_dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(addprefix $(OBJ_DIR), $(OBJ_DIRS))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(MLX)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re create_dirs
