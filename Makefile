# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 11:49:12 by dkhatri           #+#    #+#              #
#    Updated: 2023/03/30 16:38:20 by dkhatri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc
CFLAGS = -Werror -Wall -Wextra
INC_DIR = include/
SRC_DIR = src
OBJ_DIR = obj

INC_DEPS = alloc.h helper_func.h
DEPS = $(addprefix $(INC_DIR), $(INC_DEPS))

OBJ_NAME = large_alloc.o list_func.o helper_func.o \
		   mem_alloc.o mmap_alloc.o \
		   page_alloc.o zone_alloc.o

OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@$(CC) -c -o $@ $< $(CFLAGS) -I $(INC_DIR)
	@echo "\033[1m$(NAME)\033[0m : Compling $< ----> $@ \033[1;32m[OK]\033[0m"

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rc $(NAME) $(OBJS)
	@echo "Compiling $@ \033[1;32m[OK]\033[0m"
	@ranlib $(NAME)
	@echo "Indexing $@ \033[1;32m[OK]\033[0m"

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