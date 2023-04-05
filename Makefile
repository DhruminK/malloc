# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 11:49:12 by dkhatri           #+#    #+#              #
#    Updated: 2023/04/05 10:43:51 by dkhatri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc
CFLAGS = -Werror -Wall -Wextra -fPIC
INC_DIR = include/
SRC_DIR = src
OBJ_DIR = obj

INC_DEPS = alloc.h helper_func.h
DEPS = $(addprefix $(INC_DIR), $(INC_DEPS))

SRC_NAME = find_alloc.c find_realloc.c find_size.c helper_func.c mmap_alloc.c\
		   helper_func1.c large_alloc.c main_func.c mem_alloc.c mem_dealloc.c\
		   mem_realloc.c page_alloc.c page_dealloc.c zone_alloc.c zone_mem_alloc.c\
		   ft_print_func.c show_mem_alloc.c frerror.c

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@$(CC) -c -o $@ $< $(CFLAGS) -I $(INC_DIR)
	@echo "\033[1m$(NAME)\033[0m : Compling $< ----> $@ \033[1;32m[OK]\033[0m"

all: $(NAME)

$(NAME): $(OBJS)
	@gcc -dynamiclib -o $(NAME) $(OBJS)
	@echo "Compiling $@ \033[1;32m[OK]\033[0m"

clean:
	@/bin/rm -f $(OBJS)
	@/bin/rm -rf $(OBJ_DIR)
	@echo "\033[1m$(NAME)\033[0m :\
		$(OBJ_DIR) directory cleared \033[1;32m[OK]\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[1m$(NAME)\033[0m library removed \033[1;32m[OK]\033[0m"

re: clean fclean all

.PHONY: clean fclean all re
