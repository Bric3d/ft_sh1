# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/08 15:08:34 by bbecker           #+#    #+#              #
#    Updated: 2015/01/05 18:00:51 by bbecker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = sh1

F = ./srcs/

I = -I./headers

L = -L./lib -lft

TOMAKE =	$(F)main.c					\
			$(F)get_next_line.c


TOLIB	=	main.o						\
			get_next_line.o

all: $(NAME)

$(NAME):
	make -C ./lib/libft
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
