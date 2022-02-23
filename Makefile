# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 02:21:09 by gucamuze          #+#    #+#              #
#    Updated: 2022/02/23 18:25:38 by gucamuze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


EXEC_NAME		=	minishell
CC				=	clang -Wall -Wextra -Werror -g
RM				=	rm -f

SRCS_PATH		=	./srcs/
OBJ_PATH		=	./srcs/obj
LIBFT_PATH		=	./libft/
LIBFT_A			=	./libft/libft.a
INCLUDES		=	-Iincludes -lreadline $(LIBFT_A)
					
SRC_FILES		=	main.c getters.c ft_split.c prompt.c
CFILES_PATH		=	$(addprefix ${SRCS_PATH}, ${SRC_FILES})
OFILES_PATH		=	$(addprefix ${OBJ_PATH}, ${SRC_FILES})
SRC_OFILES		= 	$(CFILES_PATH:.c=.o)

%.o:%.c
				$(CC) -Iincludes -c $< -o $@

all:			${EXEC_NAME}

$(EXEC_NAME):	$(LIBFT_A) $(SRC_OFILES)
				$(CC) $(SRC_OFILES) $(INCLUDES) -o $(EXEC_NAME)

$(LIBFT_A):
				make --directory=libft

clean:
				make clean --directory=libft
				$(RM) $(SRC_OFILES)

fclean:		clean
				$(RM) $(LIBFT_A) ${EXEC_NAME}

re:			fclean all

norminette:
			norminette srcs libft includes

bonus:
			@google-chrome-stable --new-window https://youtu.be/dQw4w9WgXcQ\?t\=42	

.PHONY:	all clean fclean re norminette

