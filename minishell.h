/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:48 by jishin            #+#    #+#             */
/*   Updated: 2025/05/30 11:14:34 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define TYPE_FAIL 1
# define TYPE_SUCCESS 0
# define TYPE_INITIAL_STATUS 0
# define TYPE_ARGV_NULL 1
# define TYPE_SYNTAX_ERROR 99
# define TYPE_AMBIGUOUS_ERROR 999
# define TYPE_TOKEN_CHUNK 11
# define TYPE_TOKEN_ARGV 22
# define TYPE_TOKEN_SPACE 33
# define TYPE_TOKEN_PIPE 44
# define TYPE_TOKEN_EXEC 55
# define TYPE_TOKEN_IO_L 101
# define TYPE_TOKEN_IO_LL 102
# define TYPE_TOKEN_IO_R 103
# define TYPE_TOKEN_IO_RR 104
# define TYPE_AFTER_HEREDOC 105

# define ERROR_ISDIR 0
# define ERROR_SYSTEM 2
# define ERROR_INVALID_IDENTIFIER 500
# define ERROR_NO_SUCH_FILE_OF_DIR 50
# define ERROR_TOO_MANY_ARGS 51
# define ERROR_TOO_FEW_ARGS 52
# define ERROR_CMD_NOT_FOUND 127
# define ERROR_NUMERIC_REQUIRED 255

# define EXIT_MINISHELL 4242

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
	int				pipe_fd[2];
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
	t_cmd_list	*cmd_list;
	char		*cmd_line;
	int			exit_signal;
	pid_t		*pids;
}	t_state;

/* Init minishell */
t_state		*init_minishell(int *argc, char ***argv, char **envp);
t_env		*get_env_list(char **envp);
void		ft_sigint(int signo);
void		print_banner(void);

/* Parse - tokenize */
void		tokenize_quotation(t_token *token_list, t_state *state);
char		*handle_double_quoted_sequence(char *str, t_state *state);
void		tokenize_env_var(t_token *token_list, t_state *state);
void		tokenize_space(t_token *token_list);
void		tokenize_pipe(t_token *token_list);
void		tokenize_redirect(t_token *token_list);
void		delete_empty_token(t_token **token_list);
void		tokenize_chunk_to_argv(t_token *token_list);
void		delete_space_token(t_token **token);

/* Parse - main */
t_cmd_list	*parse(char *cmd, t_state *state);
t_cmd_list	*tokens_to_cmd_list(t_token *token_list);

/* Parse - Error handling */
void		check_syntax_error(t_token *token_list);
t_cmd_list	*handle_syntax_error(t_token *token_list);

/* Parse - utils */
char		**parse_split(char const *s, char c);
char		**split_with_delim(const char *s, char c);
char		**split_with_two_delim(char const *s, char l, char r);
char		*expand_env_in_str(char *str, int idx, t_state *state);
void		retokenize_expanded_token(t_token *token);
t_token		*create_token(int token_type, const char *str);
t_token		*add_token(t_token **token_list, size_t idx, int type, char *str);
t_cmd_list	*create_cmd_list(void);
t_cmd		*create_cmd(void);
t_cmd		*add_cmd_to_cmd_list(t_cmd_list *cmd_list);
t_cmd_redir	*add_cmd_redir(t_cmd *cmd, int type, char *file);
void		*add_cmd_argv(t_cmd *cmd, char *str, int idx);

/* Exec */
void		prompt(t_state *state);
int			set_pids(t_state *state, pid_t **pids);
void		wait_for_processes(t_state *state, pid_t *pids, int cmd_count);
int			is_full_of_space(char *str);
void		execute_child_processes(t_cmd *cmd, t_state *state, pid_t *pid);
void		handle_empty_cmd(t_cmd *cmd, pid_t *pids, int *i);

/* Exec - Pipe and Redirction */
int			check_pipe(t_cmd **cmd);
int			set_redirection(t_cmd *cmd);
void		handle_pipe_and_redirection(t_cmd *cmd);
void		close_fd(t_cmd *cmd, int fd_backup[2]);

/* Exec - Builtin */
int			is_builtin_command(t_cmd *cmd);
int			ft_exec_builtin(t_cmd *cmd, t_state *state);
int			builtin_execute_echo(t_cmd *cmd, t_state *state);
int			builtin_execute_cd(t_cmd *cmd, t_state *state);
int			builtin_execute_pwd(t_cmd *cmd, t_state *state);
int			builtin_execute_export(t_cmd *cmd, t_state *state);
int			builtin_execute_unset(t_cmd *cmd, t_state *state);
int			builtin_execute_env(t_cmd *cmd, t_state *state);
int			is_exit(t_cmd *cmd);
int			builtin_execute_exit(t_cmd *cmd, t_state *state);
int			execute_single_exit(t_cmd *cmd, t_state *state);

/* Exec - Builtin utils */
int			find_argc(char **argv);
void		ft_update_pwdenv(t_state *state);
t_env		*ft_find_return_env(char *key, t_env *env_list);
void		add_nullvalue_env(char *key, t_env *env_list);
t_env		*ft_find_env(char *env_str, t_env *env_list);

/* Heredoc */
int			has_heredoc(t_cmd_list *cmd_list, t_state *state);
void		heredoc_prompt(char *del, int fd, char *line, t_state *state);
char		*get_heredoc_delimeter(t_cmd_redir *red, int idx);
int			is_fd_valid(int fd);
void		heredoc_sigint(int signo);

/* Util - Environment variables */
t_env		*create_new_env(char *key, char *value);
t_env		*add_env(t_env *env, char *key, char *value);
char		*ft_getenv(t_state *state, char *key);
char		**get_envp(t_env *env_list);
t_env		*find_tail_env(t_env *env_list);

/* Util - Minishell ft_utils */
char		*ft_strndup(const char *s, size_t n);
int			ft_strcmp(char const *s1, char const *s2);
long long	ft_atoll(const char *str);

/* Util - Print error message*/
void		print_error_external(t_state *state, t_cmd *cmd, \
									char **envp, int err);
void		print_error_builtin(t_cmd *cmd, char *env_str, int error);
void		print_error_syntax(t_cmd *cmd, int err);

/* Clean up - memory free functions */
void		*free_2d_array(char **array);
void		*free_multiple_array(void *s1, void *s2, void *s3, void *s4);
void		free_state(t_state *state);
void		free_token(t_token *token);
void		free_token_list(t_token *token_list);
void		free_cmd_node(t_cmd *cmd);
void		*free_cmd_list(t_cmd_list *cmd_list);
void		free_cmd_redir(t_cmd *cmd);
void		unlink_tmp_file(t_cmd_list *cmd_lists);
void		exit_child_process(t_state *state, char **envp, int exit_code);

#endif
