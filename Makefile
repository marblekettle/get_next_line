NAME = get_next_line
SRCS = get_next_line.c get_next_line_utils.c
INCLUDE = .

all: $(NAME)

$(NAME):
	gcc get_next_line.c get_next_line_utils.c -o $(NAME) -D BUFFER_SIZE=10

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all

