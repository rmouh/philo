# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/04 11:23:08 by rmouhoub          #+#    #+#              #
#    Updated: 2023/11/04 11:59:23 by rmouhoub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			=	philo

LIBFT			=	libft.a

DIR_SRCS		=	srcs/mandatory
DIR_OBJS		=	objs

DIR_PARSING		=	parsing


SRCS_NAMES 		= 	$(DIR_PARSING)/parsing.c \
					$(DIR_PARSING)/routine.c\
					$(DIR_PARSING)/eat.c\
					$(DIR_PARSING)/sleep.c\
					$(DIR_PARSING)/fork.c\
					$(DIR_PARSING)/watcher.c\
					
					

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))
OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

CFLAGS			= -Wall -Werror -Wextra -g3

CC				=	cc

HEAD			= -Iincludes -Ilibft 

all				:	${NAME}

$(NAME): $(OBJS)
	make -C libft
	mv libft/libft.a .
	$(CC) -g3 $(OBJS)  ${HEAD} ${LIBFT}  -o $(NAME)
	@echo "\033[34;5mPhilo\033[0m"

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p objs/parsing

	
$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c | $(DIR_OBJS)
	$(CC)  -c $< -o $@ $(HEAD)





clean			:
					make clean -C libft
					rm -rf ${OBJS} 

fclean			:	clean
					make fclean -C libft
					rm -rf ${LIBFT}
					rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re bonus