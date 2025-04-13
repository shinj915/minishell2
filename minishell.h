/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:48 by jishin            #+#    #+#             */
/*   Updated: 2025/04/13 22:17:42 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define TYPE_FAIL 1
# define TYPE_SUCCESS 0
# define TYPE_INITIAL_STATUS 0
# define TYPE_ARGV_NULL 1
# define TYPE_SYNTAX_ERROR 99
# define TYPE_AMBIGOUS_ERROR 999
# define TYPE_TOKEN_CHUNK 11
# define TYPE_TOKEN_ARGV 22
# define TYPE_TOKEN_SPACE 33
# define TYPE_TOKEN_PIPE 44
# define TYPE_TOKEN_EXEC 55
# define TYPE_TOKEN_IO_L 101
# define TYPE_TOKEN_IO_LL 102
# define TYPE_TOKEN_IO_R 103
# define TYPE_TOKEN_IO_RR 104
# define TYPE_AFTER_HD 105

extern int	g_exit_status;

typedef struct s_token
{
	int				token_type;
	int				is_null;
	char			*str;
	char			*origin_str;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd_redir
{
	int					redir_type;
	char				*file;
	struct s_cmd_redir	*next;
}	t_cmd_redir;

typedef struct s_cmd
{
	int				cmd_type;
	int				fd[2];
	int				fd_in;
	int				fd_out;
	char			*exec_file_name;
	char			**argv;
	t_cmd_redir		*redir_list;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_cmd_list
{
	int		cmd_status;
	t_cmd	*head;
	t_cmd	*tail;
}	t_cmd_list;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_state
{
	t_env		*env_list;
	char		*cmd_line;
	char		*cmd_parse;
	t_cmd_list	*cmd_list;
}	t_state;

/* Parse - main */
t_token	*parse(char *cmd, t_state *state);
t_token	*tokenize(char *cmd, t_state *state);

/* Environment variables */
t_env	*create_new_env(char *key, char *value);
t_env	*add_env(t_env *env, char *key, char *value);
char	*ft_getenv(t_state *state, char *key);

/* Parse - tokenize quotation */
void	tokenize_quotation(t_token *token_list, t_state *state);
char	*handle_double_quoted_sequence(char *str, t_state *state);

/* Parse - utils */
t_token	*create_token(int token_type, const char *str);
t_token	*add_token(t_token **token_list, size_t idx, int type, char *str);
void	free_token(t_token *token);
char	**parse_split(char const *s, char c);

/* Minishell ft_utils */
char	*ft_strndup(const char *s, size_t n);
int	ft_strcmp(char const *s1, char const *s2);

/*Init minishell */
t_state	*init_minishell(int *argc, char ***argv, char **envp);
t_env	*get_env_list(char **envp);
void	ft_sigint(int signo);
void	print_banner(void);

/* Clean up - memory free functions */
void	*free_2d_array(char **array);
void	*free_multiple_array(void *s1, void *s2, void *s3, void *s4);

/* Test - 삭제 필요 */
void print_toklist(t_token *tok_list);

#endif
