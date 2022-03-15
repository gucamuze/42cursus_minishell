# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 02:21:09 by gucamuze          #+#    #+#              #
#    Updated: 2022/03/16 00:21:40 by adben-mc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


EXEC_NAME		=	minishell
CC				=	clang -Wall -Wextra -Werror -g
RM				=	rm -f

SRCS_PATH		=	./srcs/
BUILTINS_PATH	=	./srcs/builtins/
UTILS_PATH		=	./srcs/utils/
PARSER_PATH		=	./srcs/parser/
EXEC_PATH		=	./srcs/exec/

LIBFT_PATH		=	./libft/
LIBFT_A			=	./libft/libft.a
INCLUDES		=	-Iincludes -lreadline $(LIBFT_A)
			
BUILTINS		=	cd.c echo.c pwd.c unset.c export.c env.c
BUILTINS_W_PATH	=	$(addprefix ${BUILTINS_PATH}, ${BUILTINS})
BUILTINS_OFILES	=	$(BUILTINS_W_PATH:.c=.o)
ALL_OFILES		+=	$(BUILTINS_OFILES)
			
PARSER			=	parser.c
PARSER_W_PATH	=	$(addprefix ${PARSER_PATH}, ${PARSER})
PARSER_OFILES	=	$(PARSER_W_PATH:.c=.o)
ALL_OFILES		+=	$(PARSER_OFILES)

EXEC			=	exec.c fd.c path.c utils.c
EXEC_W_PATH	=	$(addprefix ${EXEC_PATH}, ${EXEC})
EXEC_OFILES	=	$(EXEC_W_PATH:.c=.o)
ALL_OFILES		+=	$(EXEC_OFILES)

UTILS			=	env_lst_utils.c utils.c commands_utils.c ft_split.c \
					env_utils.c commands_lst_utils.c __DEBUG.c
UTILS_W_PATH	=	$(addprefix ${UTILS_PATH}, ${UTILS})
UTILS_OFILES	=	$(UTILS_W_PATH:.c=.o)
ALL_OFILES		+=	$(UTILS_OFILES)

SRC_FILES		=	main.c prompt.c signals.c
SRC_PATH		=	$(addprefix ${SRCS_PATH}, ${SRC_FILES})
SRC_OFILES		= 	$(SRC_PATH:.c=.o)
ALL_OFILES		+=	$(SRC_OFILES)

%.o:%.c
				$(CC) -Iincludes -c $< -o $@

all:			${EXEC_NAME}

$(EXEC_NAME):	$(LIBFT_A) $(SRC_OFILES) $(BUILTINS_OFILES) $(UTILS_OFILES) $(PARSER_OFILES) $(EXEC_OFILES)
				$(CC) $(ALL_OFILES) $(INCLUDES) -o $(EXEC_NAME)

$(LIBFT_A):
				make --directory=libft

clean:
				make clean --directory=libft
				$(RM) $(ALL_OFILES)

fclean:		clean
				$(RM) $(LIBFT_A) ${EXEC_NAME}

re:			fclean all

norminette:
			norminette srcs libft includes

bonus:
			@google-chrome-stable --new-window https://youtu.be/dQw4w9WgXcQ\?t\=42	

.PHONY:	all clean fclean re norminette

