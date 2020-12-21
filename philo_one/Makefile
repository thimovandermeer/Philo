# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbennink <jbennink@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/16 09:21:05 by jbennink      #+#    #+#                  #
#    Updated: 2020/12/21 13:57:06 by thimovander   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

SRCS = 	create_philos.c \
		main.c \
		philo_loop.c \
		utils.c \
		validate_inputs.c

OBJS = $(SRCS:.c=.o)

INCL = philosophers.h

FLAGS = -Wall -Wextra -Werror

OS = $(shell uname)
ifeq ($(OS),Linux)
	FLAGS += -pthread
endif

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(INCL)
	gcc $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
