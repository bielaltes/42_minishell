# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsebasti <jsebasti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 00:35:07 by jsebasti          #+#    #+#              #
#    Updated: 2023/05/07 01:23:30 by jsebasti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= minishell
INC_DIR		= INC/
MKFL		= Makefile
SRC_DIR		= SRC/
OBJ_DIR		= OBJ/


# ----Libraryes----
PW_HEADER	= $(INC_DIR)/minishell.h
LIB			= Libs/Libft/libft.a
LIB_M 		= Libs/Libft/
PRINTF		= Libs/printf/libftprintf.a
PRINTF_M	= Libs/printf/
# =============

# -------------
RM = rm -rf
MP = mkdir -p
CFLAGS = -Werror -Wextra -Wall -O2 #-fsanitize=address
LIBC = ar -rcs
# =============

SRC_L	=	minishell.c 				\
			parser/lexer.c				\
			execute/exec.c				\
			built-ins/cd.c				\
			built-ins/env.c				\
			built-ins/pwd.c				\
			built-ins/echo.c			\
			built-ins/exit.c			\
			built-ins/unset.c			\
			built-ins/export.c			\


SRC = $(addprefix $(SRC_DIR), $(SRC_L))

# -------------
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
DEP = $(addsuffix .d, $(basename $(OBJ)))
# =============

$(OBJ_DIR)%.o: %.c $(MKFL)
	@$(MP) $(dir $@)
	$(CC) $(CFLAGS) -MMD -I $(INC_DIR) -c $< -o $@

all:
	@$(MAKE) $(NAME)

$(NAME):: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME)::
	@echo "Hello, Minishell already compiled 😇"

-include $(DEP)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE)

.PHONY: all clean fclean re
