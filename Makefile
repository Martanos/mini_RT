# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 14:14:50 by malee             #+#    #+#              #
#    Updated: 2025/03/08 11:15:50 by malee            ###   ########.fr        #
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
SRC_PARSING		= parser_main.c
SRC_PARSING_CREATE_OBJ = create_amb.c create_cam.c create_cylinder.c \
						create_light.c create_plane.c create_sphere.c\
						create_cone.c
SRC_PARSING_READ_FILE = read_file_main.c read_data_utils.c process_buffer.c
SRC_PARSING_UTILS	= parser_rgb.c parser_xyz.c parser_atod.c parser_utils.c
SRC_PARSING_HANDLE_EXTRA_DATA = txm_handler.c bpm_handler.c mat_handler.c extra_data.c
SRC_UTILITIES	= handle_errors.c handle_warnings.c mem_management.c \
					 mlx_utils.c p_node_utils.c
SRC_RENDER		= check_cylinder_main.c check_cylinder_side.c \
					check_cylinder_caps.c check_cylinder_utils.c check_plane.c check_sphere.c \
					intersection_check.c intersection_check_util.c ray_utils.c \
					renderplane.c tracing.c render_main.c uv_mapping.c \
					xpm_utils.c specular.c reflections.c checkerboard.c \
					check_cone_main.c check_cone_surface.c check_cone_utils.c check_cone_utils2.c \
					bump_maps.c
SRCS			= $(addprefix $(SRC_DIR)/01_main/, $(SRC_MAIN)) \
					$(addprefix $(SRC_DIR)/02_parser/, $(SRC_PARSING)) \
					$(addprefix $(SRC_DIR)/02_parser/read_file/, $(SRC_PARSING_READ_FILE)) \
					$(addprefix $(SRC_DIR)/02_parser/create_obj/, $(SRC_PARSING_CREATE_OBJ)) \
					$(addprefix $(SRC_DIR)/02_parser/utils/, $(SRC_PARSING_UTILS)) \
					$(addprefix $(SRC_DIR)/02_parser/handle_extra_data/, $(SRC_PARSING_HANDLE_EXTRA_DATA)) \
					$(addprefix $(SRC_DIR)/utilities/, $(SRC_UTILITIES)) \
					$(addprefix $(SRC_DIR)/03_render_logic/, $(SRC_RENDER))


# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Program name (of executable)
NAME		= miniRT

# Targets
.PHONY: all
all:        $(NAME)

$(NAME):		$(LIBFT) $(LIBVECT) $(LIBRGB) $(MLX) $(OBJS)
	@mkdir -p $(@D)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBFT_FLAGS) $(LIBVECT) $(LIBVECT_FLAGS) $(LIBRGB) $(LIBRGB_FLAGS) $(MLX) $(LDFLAGS) -o $@ > /dev/null 2>&1
	@echo "$(GREEN)$(NAME) has been compiled.$(RESET)"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@ 2>&1 | tee /dev/stderr | sed 's/^/\033[0;31m/'; \
	if [ $$? -ne 0 ]; then echo "$(RED)Compilation failed for $<$(RESET)"; fi

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR) > /dev/null 2>&1

$(LIBVECT):
	@echo "$(YELLOW)Compiling libvect...$(RESET)"
	@make -C $(LIBVECT_DIR) > /dev/null 2>&1

$(LIBRGB):
	@echo "$(YELLOW)Compiling librgb...$(RESET)"
	@make -C $(LIBRGB_DIR) > /dev/null 2>&1

$(MLX):
	@echo "$(YELLOW)Compiling MLX...$(RESET)"
	@make -C $(MLX_DIR) > /dev/null 2>&1

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
	@echo "$(GREEN)$(NAME) and all object files have been removed.$(RESET)"

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
