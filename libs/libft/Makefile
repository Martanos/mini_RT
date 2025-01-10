# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 20:12:49 by malee             #+#    #+#              #
#    Updated: 2025/01/10 16:59:27 by malee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Config
NAME = libft.a
CC = cc
# -O1, -O2, -O3, and -Ofast Increasing level of compiler aggresiveness
# set lower if encountering bugs -Os for space priority
CFLAGS = -Wall -Wextra -Werror -Ofast -g
AR = ar rcs
RM = rm -rf

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Sources
CFILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		 ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c \
		 ft_strncmp.c ft_strdup.c ft_striteri.c ft_substr.c ft_strjoin.c \
		 ft_strtrim.c ft_split.c ft_toupper.c ft_tolower.c ft_atoi.c \
		 ft_itoa.c ft_calloc.c ft_memset.c ft_bzero.c ft_memcpy.c \
		 ft_memmove.c ft_memchr.c ft_memcmp.c ft_lstnew.c ft_lstadd_front.c \
		 ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
		 ft_lstiter.c ft_lstmap.c ft_strmapi.c ft_strcmp.c
SRC_DIR = ./srcs
SRCS = $(addprefix $(SRC_DIR)/, $(CFILES))

# Helper files
INCLUDE_DIR = includes

#Object creation
OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/, $(CFILES:%.c=%.o))

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^
	@echo "$(GREEN)$(NAME) created successfully.$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)$(OBJ_DIR) directory created.$(RESET)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)$(NAME) object files cleaned successfully.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)$(NAME) removed successfully.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
