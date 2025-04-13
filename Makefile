NAME = minishell
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g -I./
LDFLAGS = -lreadline
CC = cc

# test.c = 파싱 테스트를 위한 소스 파일, 추후 제거 필요
SRCS = main.c \
		test.c \
		src/free/free_utils.c \
		src/parse/expand_env_in_str.c \
		src/parse/parse_main.c \
		src/parse/tokenize_quotation.c \
		src/parse/util_split.c \
		src/parse/util_token.c \
		src/util/env.c \
		src/util/ft_utils.c \
		src/util/init.c

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
