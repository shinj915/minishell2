NAME = minishell
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g -I./
LDFLAGS = -lreadline
CC = cc
SRCS = main.c \
		test.c \
		src/parse/parse_main.c \
		src/parse/token_utils.c

OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft all
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C ./libft clean
	rm -rf $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
