NAME = philo

SRC = srcs/parsing.c srcs/utils.c srcs/philo.c srcs/philo_funcs.c \
	  srcs/init.c srcs/more_utils.c srcs/threads.c srcs/utils3.c \

OBG = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=thread -g3 -pthread

all	:	$(NAME)

$(NAME) : $(OBG)
		$(CC) $(CFLAGS) $(OBG) -o $(NAME)

%.o	 : %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBG)

fclean:
	rm -rf $(OBG) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBG)