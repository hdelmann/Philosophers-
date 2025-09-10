# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 10:34:36 by hdelmann          #+#    #+#              #
#    Updated: 2023/05/09 10:54:11 by hdelmann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := philo
CC        := gcc
FLAGS    := -Wall -Wextra -Werror #-O3 #-g -fsanitize=thread

SRCS        :=      fct/main.c \
					fct/initroutine.c \
					fct/utils.c \
					fct/eat.c \
					fct/free.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

RM		    := rm -f

${NAME}:	${OBJS}
			${CC} ${FLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

bonus:		all

clean:
			@ ${RM} fct/*.o

fclean:		clean
			@ ${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re


