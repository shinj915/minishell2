
NAME = minishell

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g -I./
LDFLAGS = -lreadline
CC = cc

RMFLAGS = -rf
RM = rm

SRCS = main.c \
		src/init/init.c \
		src/init/env.c \
		src/init/utils.c \
		src/parse/parse_main.c \
		src/free_struct.c \
		src/free_utils.c \
		src/prompt.c

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C./libft all
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C ./libft clean
	$(RM) $(RMFLAGS) $(OBJS)

fclean: clean
	make -C ./libft fclean
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
