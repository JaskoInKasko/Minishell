CC = cc
CFLAGS = -Wall -Wextra -Werror
RLFLAG = -lreadline
SRC = test.c
OBJ = $(SRC:.c=.o)
NAME = minishell

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(RLFLAG) $(OBJ) -o $(NAME)

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
