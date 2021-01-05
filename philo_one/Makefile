# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: thvan-de <thvan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/16 09:21:05 by jbennink      #+#    #+#                  #
#    Updated: 2021/01/05 09:30:18 by thvan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

SRCS = 	create_philos.c \
		main.c \
		philo_loop.c \
		utils.c \
		validate_inputs.c \
		free_functions.c \
		libft_func.c

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

#  -fsanitize=thread
