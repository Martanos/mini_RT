# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 17:25:16 by malee             #+#    #+#              #
#    Updated: 2025/02/06 22:31:55 by malee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = librgb.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast -g
AR = ar rcs
RM = rm -rf
INCLUDE_DIR = includes
SRC_DIR = ./srcs
SRC_FILES = functions1.c functions2.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR = ./obj
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)$(OBJ_DIR) directory created.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)$(NAME) created successfully.$(RESET)"

clean:
	@$(RM) $(OBJ)
	@echo "$(GREEN)$(OBJ) object files cleaned successfully.$(RESET)"

fclean: clean
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)$(OBJ_DIR) object files cleaned successfully.$(RESET)"
	@$(RM) $(NAME)
	@echo "$(GREEN)$(NAME) removed successfully.$(RESET)"

re: fclean all
