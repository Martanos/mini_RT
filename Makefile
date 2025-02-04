# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 14:14:50 by malee             #+#    #+#              #
#    Updated: 2025/02/04 16:28:12 by seayeo           ###   ########.fr        #
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
LIBVECT_DIR	= libs/libvect
INC_DIR		= include

# Include paths
INCS		= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(LIBVECT_DIR) -I$(LIBRGB_DIR)
LIBFT		= $(LIBFT_DIR)/libft.a
LIBVECT		= $(LIBVECT_DIR)/libvect.a
LIBRGB		= $(LIBRGB_DIR)/librgb.a
LIBS		= -L$(LIBFT_DIR) -lft -L$(LIBVECT_DIR) -lvect -L$(LIBRGB_DIR) -lrgb

# Source files
SRCS =	$(addprefix $(SRCS_DIR)/,\
		main.c \
		ray_utils.c \
		# ...existing code...
		)
# Remove vector_utils.c from SRCS list

# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Program name (of executable)
NAME		= minirt

# Targets
.PHONY: all
all:        $(NAME)

$(NAME):		$(LIBFT) $(OBJS)
	@mkdir -p $(@D)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LIBS) -o $@ $(LDFLAGS)
	@echo "$(GREEN)$(NAME) has been compiled.$(RESET)"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR)

.PHONY: clean fclean re
clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(LIBVECT_DIR) clean
	@echo "$(RED)Object files have been removed.$(RESET)"

fclean:			clean
	@echo "$(YELLOW)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(LIBVECT_DIR) fclean
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



