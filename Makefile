# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/02 14:59:03 by nkellum           #+#    #+#              #
#    Updated: 2019/08/01 13:05:03 by nkellum          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c command.c builtin.c env.c cd.c edit_env.c aux.c

FLAGS = -Wextra -Wall -Werror

ifndef VERBOSE
.SILENT:
endif

all:$(NAME)

$(NAME): $(SRC)
	make -C libft
	gcc $(FLAGS) -o $(NAME) $(SRC) libft/libft.a
	echo "$(NAME) compiled."

clean:
	make -C libft clean
	echo "\033[32mObject files deleted.\033[0m"

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
