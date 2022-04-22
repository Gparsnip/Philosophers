
NAME = philo
CC = gcc
FLAGS = -Wall -Wextra -Werror
OPTION = -c
SRCS = philo.c \
		simulation.c \
		philo_init.c \

OBJS_SRCS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME) : $(OBJS_SRCS)
		@$(CC) $(FLAGS) $(OPTION) $(SRCS)
		@$(CC) $(OBJS_SRCS) -o $(NAME)
clean:
		rm -f $(OBJS_SRCS)
fclean: clean
		rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
