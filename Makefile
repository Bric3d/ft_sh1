# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/08 15:08:34 by bbecker           #+#    #+#              #
#    Updated: 2015/03/17 11:37:15 by bbecker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell1

F = ./srcs/

I = -I./headers

L = -L./lib -lft

TOMAKE =	$(F)main.c					\
			$(F)cmd.c					\
			$(F)builtinschecker.c		\
			$(F)env.c					\
			$(F)exit.c					\
			$(F)setenv.c				\
			$(F)unsetenv.c				\
			$(F)ft_execve.c				\
			$(F)findbin.c				\
			$(F)split.c					\
			$(F)get_next_line.c			\
			$(F)errors.c				\
			$(F)utilities.c				\
			$(F)realloctab.c			\
			$(F)cd.c


TOLIB	=	main.o						\
			cmd.o						\
			builtinschecker.o			\
			env.o						\
			exit.o						\
			setenv.o					\
			unsetenv.o					\
			ft_execve.o					\
			findbin.o					\
			split.o						\
			get_next_line.o				\
			errors.o					\
			utilities.o					\
			realloctab.o				\
			cd.o

all: $(NAME)

$(NAME):
	make -C ./lib/libft
	cp ../libft.a ./lib/
	gcc -c -Wall -Werror -Wextra $(TOMAKE) $(I) $(L)
	gcc -Wall -Werror -Wextra $(I) $(L) -o $(NAME) $(TOLIB)

test:
	make -C ./lib/libft test
	cp ../libft.a ./lib/
	gcc -c -g -Wall -Werror -Wextra $(TOMAKE) $(I) $(L)
	gcc -g -Wall -Werror -Wextra $(I) $(L) -o $(NAME) $(TOLIB)

clean :
	/bin/rm -rf $(TOLIB)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f ./lib/libft.a

re: fclean all

.PHONY: fclean clean all test
