# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 00:35:07 by jsebasti          #+#    #+#              #
#    Updated: 2023/06/27 14:57:34 by baltes-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= minishell
INC_DIR		= INC/
MKFL		= Makefile
SRC_DIR		= SRC/
OBJ_DIR		= OBJ/


# ----Libraryes----
PW_HEADER	= $(INC_DIR)/minishell.h
LIB			= $(INC_DIR)/libft/libft.a
LIB_M 		= $(INC_DIR)/libft/
# =============

# -------------
RM = rm -rf
MP = mkdir -p
CFLAGS =  -g -Wall -Wextra -Werror -fsanitize=address
LIBC = ar -rcs
# =============

SRC_L	=	main/minishell.c 				\
			main/signals.c					\
			main/end.c						\
			parser/lexer.c					\
			parser/ft_split_tokens.c 		\
			parser/ft_split_tokens_utils.c	\
			parser/assing.c 				\
			parser/token_type.c 			\
			parser/syntax.c					\
			parser/get_syntax.c				\
			parser/expand.c					\
			parser/misuse.c					\
			execute/exec.c					\
			execute/get_path.c				\
			execute/redirs.c 				\
			built-ins/cd.c					\
			built-ins/env.c					\
			built-ins/pwd.c					\
			built-ins/echo.c				\
			built-ins/exit.c				\
			built-ins/unset.c				\
			built-ins/utils.c				\
			built-ins/utils2.c				\
			built-ins/export.c				\


SRC = $(addprefix $(SRC_DIR), $(SRC_L))

# -------------
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
DEP = $(addsuffix .d, $(basename $(OBJ)))
# =============

all:
	@$(MAKE) -C $(LIB_M) --no-print-directory
	@$(MAKE) $(NAME) --no-print-directory

$(OBJ_DIR)%.o: %.c $(MKFL)
	@$(MP) $(dir $@)
	@$(CC) $(CFLAGS) -MMD -I $(INC_DIR) -I$(HOME)/.brew/opt/readline/include -c $< -o $@

$(NAME):: $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -lreadline -L$(HOME)/.brew/opt/readline/lib -o $(NAME)

$(NAME)::
	@echo "Hello, Minishell already compiled 😇"

-include $(DEP)

clean:
	@$(MAKE) clean -C $(LIB_M) --no-print-directory
	$(RM) $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIB_M) --no-print-directory
	$(RM) $(NAME)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) --no-print-directory

.PHONY: all clean fclean re
