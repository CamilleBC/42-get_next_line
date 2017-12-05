# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 18:12:06 by cbaillat          #+#    #+#              #
#    Updated: 2017/12/05 19:47:03 by cbaillat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET_EXEC  := get_next_line

#directories
SRCS_DIR  := ./
INC_DIR   := ./
BUILD_DIR := ./build
LIB_DIR   := ./libft

# src / obj files
SRCS    :=	main.c \
			get_next_line.c
OBJECTS := $(patsubst %,$(BUILD_DIR)/%,$(SRCS:.c=.o))
# objects dependencies
DEPS       = $(OBJECTS:.o:.d)
DEPS_FLAGS = -MD -MP

# # compiler and flags
CC     := gcc
CFLAGS := -g  -Wall -Wextra -Werror

# # libraries
LIBS := ft
LIB_FLAGS := -L$(LIB_DIR) -l$(LIBS)

# echo output colours
CYAN = \e[1;36m
RED  = \033[1;31m
WHITE  = \033[1;37m
NC   = \033[0m

.PHONY: all clean fclean re

all:
	@mkdir -p $(BUILD_DIR)
	@make -C $(LIB_DIR)/
	@make $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJECTS)
	@echo "[Building ${RED}executable${NC}]"
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIB_FLAGS) -o $(TARGET_EXEC)

$(BUILD_DIR)/%.o:$(SRCS_DIR)/%.c
	@echo "[Building $@...]"
	@$(CC) $(CFLAGS) $(DEPS_FLAGS) -I $(INC_DIR) -o $@ -c $<

clean:
	@echo "[Cleaning ${RED}executable${NC} objects]"
	@make clean -C $(LIB_DIR)
	@rm -rf $(BUILD_DIR)

fclean: clean
	@echo  "[Cleaning ${RED}executable${NC}]"
	@make fclean -C $(LIB_DIR)
	@rm -rf $(TARGET_EXEC)

re: fclean all

-include $(DEPS)
