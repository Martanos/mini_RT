# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 14:14:50 by malee             #+#    #+#              #
#    Updated: 2025/02/14 13:22:31 by malee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RESET		= \033[0m

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

# Directories
SRC_DIR		= srcs
OBJ_DIR		= obj
LIBFT_DIR	= libs/libft
LIBRGB_DIR	= libs/librgb
LIBVECT_DIR	= libs/libvect
INC_DIR		= include

# Include paths
INCS		= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(LIBVECT_DIR) -I$(LIBRGB_DIR)
LIBFT		= $(LIBFT_DIR)/libft.a
LIBVECT		= $(LIBVECT_DIR)/libvect.a
LIBRGB		= $(LIBRGB_DIR)/librgb.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft
LIBVECT_FLAGS	= -L$(LIBVECT_DIR) -lvect
LIBRGB_FLAGS	= -L$(LIBRGB_DIR) -lrgb

# Add MLX library paths and flags
MLX_DIR     = minilibx-linux
MLX         = $(MLX_DIR)/libmlx.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11
LDFLAGS     = $(MLX_FLAGS) -lm

# Source files
SRC_MAIN		= main.c
SRC_LEXER		= read_file_main.c read_data_utils.c
SRC_PARSING		= create_amb.c create_cam.c create_cone.c create_cylinder.c \
					create_light.c create_plane.c create_sphere.c \
					extra_data.c extra_data_utils.c \
					parser_main.c parser_atod.c parser_error_utils.c \
					parser_list_utils.c parser_populate.c parser_rgb.c \
					parser_utils.c parser_xyz.c
SRC_UTILITIES	= fatal.c exit.c misc.c memory_management.c \
					master_management.c
SRC_RENDER		= check_cone.c check_cylinder.c check_plane.c check_sphere.c \
					intersection_checks.c ray_utils.c renderplane.c tracing.c \
					render_main.c texture_mapping.c xpm_utils.c
SRCS			= $(addprefix $(SRC_DIR)/01_main/, $(SRC_MAIN)) \
					$(addprefix $(SRC_DIR)/02_lexer/, $(SRC_LEXER)) \
					$(addprefix $(SRC_DIR)/03_parser/, $(SRC_PARSING)) \
					$(addprefix $(SRC_DIR)/utilities/, $(SRC_UTILITIES)) \
					$(addprefix $(SRC_DIR)/04_render_logic/, $(SRC_RENDER))


# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Program name (of executable)
NAME		= mini_rt

# Targets
.PHONY: all
all:        $(NAME)

$(NAME):		$(LIBFT) $(LIBVECT) $(LIBRGB) $(MLX) $(OBJS)
	@mkdir -p $(@D)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBFT_FLAGS) $(LIBVECT) $(LIBVECT_FLAGS) $(LIBRGB) $(LIBRGB_FLAGS) $(MLX) $(LDFLAGS) -o $@
	@echo "$(GREEN)$(NAME) has been compiled.$(RESET)"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(LIBVECT):
	@echo "$(YELLOW)Compiling libvect...$(RESET)"
	@make -C $(LIBVECT_DIR)

$(LIBRGB):
	@echo "$(YELLOW)Compiling librgb...$(RESET)"
	@make -C $(LIBRGB_DIR)

$(MLX):
	@echo "$(YELLOW)Compiling MLX...$(RESET)"
	@make -C $(MLX_DIR)

.PHONY: clean fclean re
clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(LIBVECT_DIR) clean
	@make -C $(LIBRGB_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "$(RED)Object files have been removed.$(RESET)"

fclean:			clean
	@echo "$(YELLOW)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(LIBVECT_DIR) fclean
	@make -C $(LIBRGB_DIR) fclean
	@echo "$(RED)$(NAME) and all object files have been removed.$(RESET)"

re:				fclean all

# Debugging targets
.PHONY: vg_supp vg_leak vg_all gdb_tui

vg_supp:	$(NAME)
	@echo "$(YELLOW)Running Valgrind with suppressions...$(RESET)"
	@valgrind --suppressions=mlx.supp ./$(NAME)

vg_leak:	$(NAME)
	@echo "$(YELLOW)Running Valgrind leak check...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

vg_all:		$(NAME)
	@echo "$(YELLOW)Running Valgrind full check...$(RESET)"
	@valgrind --suppressions=readline.supp \
		--leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

gdb_tui: $(NAME)
	@echo "$(YELLOW)Running gdb with tui (text user interface)...$(RESET)"
	@gdb --tui ./$(NAME)

# Generate dependency files
DEPS = $(OBJS:.o=.d)
-include $(DEPS)



