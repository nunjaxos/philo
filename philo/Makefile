CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -I./includes
NAME = philo
SRC = src/main.c src/init.c src/monitor.c src/parsing.c src/philo_funcs.c src/threads.c src/utils.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

test: $(NAME)
	./$(NAME)

all: $(NAME)
