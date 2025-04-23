NAME = minishell
CFLAGS = -Wall -Werror -Wextra -g -I./ #-fsanitize=address
LDFLAGS = -lreadline
CC = cc

SRCS = main.c \
		test.c \
		src/free/free_utils.c \
		src/free/free.c \
		src/parse/delete_token.c \
		src/parse/error_check_syntax_error.c \
		src/parse/error_handle_syntax_error.c \
		src/parse/parse_main.c \
		src/parse/tokenize_chunk_to_argv.c \
		src/parse/tokenize_env_var_util.c \
		src/parse/tokenize_env_var.c \
		src/parse/tokenize_pipe.c \
		src/parse/tokenize_quotation_util.c \
		src/parse/tokenize_quotation.c \
		src/parse/tokenize_redirect_util.c \
		src/parse/tokenize_redirect.c \
		src/parse/tokenize_space.c \
		src/parse/tokens_to_cmd_list.c \
		src/parse/util_cmd_list_create.c \
		src/parse/util_cmd_list_free.c \
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
