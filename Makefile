NAME = get_next_line
SRCS = get_next_line.c get_next_line_utils.c
INCLUDE = .
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -g testmain.c $(SRCS) -o $(NAME) -D BUFFER_SIZE=1

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all

