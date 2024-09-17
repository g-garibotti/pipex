# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 14:06:57 by ggaribot          #+#    #+#              #
#    Updated: 2024/09/17 14:18:56 by ggaribot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            =       pipex

SRC_DIR         =       srcs/

OBJ_DIR     	=   	objs/

SRCS            =       main.c

vpath %.c $(SRC_DIR)

OBJS            =       $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

CC				=       cc

CFLAGS          =       -g3 -Wall -Wextra -Werror

LIB             =       libft/libft.a

INCLUDES        =       -I includes/ -I libft/includes/

RM				=       rm -f

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
END=\033[0m
BOLD_START=\e[1m
BOLD_END=\e[0m

ifeq ($(debug), true)
        CFLAGS += -g3 -fsanitize=address,undefined
endif

define PRINT_LOADING
        @printf "$(GREEN)Compiling libft["
        @for i in $(shell seq 0 10 100); do \
                printf "▓"; \
                sleep 0.1; \
        done
        @printf "] 100%%$(RESET)\n$(END)"
endef

all:                    $(LIB) ${NAME}
							@echo "$(GREEN)$(BOLD_START)${NAME} created$(BOLD_END)$(END)"

${NAME}:               	${OBJS}
							$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

$(LIB): 			   
						@$(PRINT_LOADING) 
						$(MAKE) --no-print-directory -C ./libft/

$(OBJS):                $(OBJ_DIR)%.o: %.c
							@echo "$(BLUE)Compiling: $@ $(END)"
							mkdir -p $(OBJ_DIR)
							$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
						$(RM) -r $(OBJ_DIR)
						${RM} ${OBJS}
						@echo "$(RED)clean libft$(END)"
						$(MAKE) --no-print-directory clean -C ./libft/
						@echo "$(GREEN)$(BOLD_START)Clean done$(BOLD_END)$(END)"

fclean: clean
						${RM} ${NAME}
						@echo "$(RED)fclean libft$(END)"
						$(MAKE) --no-print-directory fclean -C ./libft/
						@echo "$(GREEN)$(BOLD_START)Fclean done$(BOLD_END)$(END)"

re: fclean all

.PHONY: all clean fclean re bonus libft
.SILENT: