
NAME = minishell

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g -I./
CC = cc

RMFLAGS = -rf
RM = rm

SRCS = main.c \
		src/init/init.c

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C./libft all
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

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
