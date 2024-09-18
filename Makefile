# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 13:09:24 by ggaribot          #+#    #+#              #
#    Updated: 2024/09/18 13:15:05 by ggaribot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS_DIR = srcs
MAIN_SRCS = main.c
PARSING_SRCS = parse_args.c
EXECUTION_SRCS = execute_commands.c
UTILS_SRCS = error_handling.c

SRCS = $(addprefix $(SRCS_DIR)/main/, $(MAIN_SRCS)) \
       $(addprefix $(SRCS_DIR)/parsing/, $(PARSING_SRCS)) \
       $(addprefix $(SRCS_DIR)/execution/, $(EXECUTION_SRCS)) \
       $(addprefix $(SRCS_DIR)/utils/, $(UTILS_SRCS))

# Object files
OBJS_DIR = objs
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Dependencies
DEPS = $(OBJS:.o=.d)

# Libft
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
    @$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -o $(NAME)
    @echo "$(BLUE)$(NAME) created!$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
    @mkdir -p $(@D)
    @printf "$(YELLOW)Compiling $<... $(RESET)"
    @if $(CC) $(CFLAGS) -MMD -MP -I./includes -Ilibft -c $< -o $@ 2>/dev/null; then \
        printf "$(GREEN)Done!$(RESET)\n"; \
    else \
        printf "$(RED)Failed!$(RESET)\n"; \
        exit 1; \
    fi

$(LIBFT):
    @echo "$(YELLOW)Compiling libft...$(RESET)"
    @$(MAKE) -C libft > /dev/null 2>&1
    @echo "$(GREEN)libft compilation done!$(RESET)"

clean:
    @echo "$(YELLOW)Cleaning up...$(RESET)"
    @$(MAKE) -C libft clean > /dev/null
    @rm -rf $(OBJS_DIR)
    @echo "$(GREEN)Clean done!$(RESET)"

fclean: clean
    @echo "$(YELLOW)Full cleanup...$(RESET)"
    @$(MAKE) -C libft fclean > /dev/null
    @rm -f $(NAME)
    @echo "$(GREEN)Full cleanup done!$(RESET)"

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
