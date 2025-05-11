/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:33:30 by jishin            #+#    #+#             */
/*   Updated: 2025/05/11 19:58:14 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_redirection(t_cmd *cmd)
{
	t_cmd_redir	*red;

	red = cmd->redir_list;
	while (red != NULL)
	{
		if (red->redir_type == TYPE_TOKEN_IO_R)
			cmd->redir_fd_out = open(red->file, O_CREAT | \
									 O_WRONLY | O_TRUNC, 0644);
		else if (red->redir_type == TYPE_TOKEN_IO_RR)
			cmd->redir_fd_out = open(red->file, O_CREAT | \
									 O_WRONLY | O_APPEND, 0644);
		else if (red->redir_type == TYPE_TOKEN_IO_L
			|| red->redir_type == TYPE_AFTER_HEREDOC)
			cmd->redir_fd_in = open(red->file, O_RDONLY);
		if (cmd->redir_fd_out == -1 || cmd->redir_fd_in == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(red->file, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return (1);
		}
		red = red->next;
	}
	return (0);
}

void	handle_pipe_and_redirection(t_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		close(cmd->pipe_fd[0]);
		dup2(cmd->pipe_fd[1], 1);
	}
	if (cmd->prev != NULL)
	{
		dup2(cmd->prev->pipe_fd[0], 0);
		close(cmd->prev->pipe_fd[0]);
		close(cmd->prev->pipe_fd[1]);
	}
	if (cmd->redir_fd_in != 0)
		dup2(cmd->redir_fd_in, 0);
	if (cmd->redir_fd_out != 1)
		dup2(cmd->redir_fd_out, 1);
}

char	*get_exec_path(t_cmd *cmd, t_state *state)
{
	char	*path;
	char	*temp_path;
	char	**path_list;
	int		i;

	path_list = ft_split(ft_getenv(state, "PATH"), ':');
	if (!path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		temp_path = ft_strjoin(path_list[i], "/");
		path = ft_strjoin(temp_path, cmd->exec_file_name);
		free(temp_path);
		if (access(path, F_OK) == 0)
		{
			free_2d_array(path_list);
			return (path);
		}
		free(path);
		i++;
	}
	free_2d_array(path_list);
	return (NULL);
}

void	check_path_error(t_cmd *cmd, t_state *state, char **path)
{
	struct stat	st;

	if (ft_strchr((*path), '/'))
	{
		if (stat((*path), &st) == 0 && S_ISDIR(st.st_mode))
			print_error_external(cmd, ERROR_ISDIR);
		if (access((*path), X_OK))
			print_error_external(cmd, ERROR_SYSTEM);
	}
	else
		(*path) = get_exec_path(cmd, state);
	if (!(*path))
		print_error_external(cmd, ERROR_CMD_NOT_FOUND);
}

void	execute_child_cmd(t_cmd *cmd, t_state *state, char **envp)
{
	char	*path;
	int		result;

	path = cmd->exec_file_name;
	if (set_redirection(cmd))
		exit(1);
	handle_pipe_and_redirection(cmd);
	result = ft_exec_builtin(cmd, state);
	if (result != -1)
		exit(result);
	check_path_error(cmd, state, &path);
	execve(path, cmd->argv, envp);
	perror("minishell: execve failed");
	exit(127);
}

void	close_fd(t_cmd *cmd, int fd_backup[2])
{
	if (cmd->prev != NULL)
		close(cmd->prev->pipe_fd[0]);
	close(cmd->pipe_fd[1]);
	if (cmd->next == NULL)
		close(cmd->pipe_fd[0]);
	if (cmd->redir_fd_in != 0)
		close(cmd->redir_fd_in);
	if (cmd->redir_fd_out != 1)
		close(cmd->redir_fd_out);
	dup2(fd_backup[0], 0);
	dup2(fd_backup[1], 1);
	close(fd_backup[0]);
	close(fd_backup[1]);
}

void	execute_child_processes(t_cmd *cmd, t_state *state, pid_t *pid, int fd_backup[2])
{
	char	**envp;

	envp = get_envp(state->env_list);
	*pid = fork();
	if (*pid < 0)
	{
		perror("fork");
		return ;
	}
	if (*pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		execute_child_cmd(cmd, state, envp);	
	}
	else
		close_fd(cmd, fd_backup);
	free(envp);
}

int	check_pipe_and_cmd(t_cmd **cmd)
{
	if(pipe((*cmd)->pipe_fd) == -1)
	{
		ft_putendl_fd("minishell: Broken pipe", 2);
		g_exit_status = 1;
		return (1);
	}
	if ((*cmd)->argv[0] == NULL || (*cmd)->argv[0][0] == '\0')
	{
		ft_putendl_fd("minishell: : command not found", 2);
		set_redirection(*cmd);
		(*cmd) = (*cmd)->next;
		g_exit_status = 127;
		return (127);
	}
	return (0);
}

int	get_cmd_exit_code(t_cmd *cmd, t_state *state, pid_t *pid)
{
	int	fd_backup[2];
	int	result;

	fd_backup[0] = dup(STDIN_FILENO);
	fd_backup[1] = dup(STDOUT_FILENO);
	result = check_pipe_and_cmd(&cmd);
	if (result > 0)
		return (result);
	if (is_builtin_command(cmd) && cmd->prev == NULL && cmd->next == NULL)
	{
		set_redirection(cmd);
		result = ft_exec_builtin(cmd, state);
		*pid = -1;
	}
	else
		execute_child_processes(cmd, state, pid, fd_backup);
	return (result);
}

int	execute_cmd(t_cmd_list *cmd_list, t_state *state)
{
	pid_t			*pids;
	t_cmd			*cmd;
	int				result;
	int				i;

	result = 0;
	i = 0;
	if (!set_pids(cmd_list, &pids))
		return (1);
	cmd = cmd_list->head;
	while (cmd != NULL)
	{
		result = get_cmd_exit_code(cmd, state, &pids[i]);
		if (result == 4242)
		{
			free(pids);
			return (4242);
		}
		cmd = cmd->next;
		i++;
	}
	wait_for_processes(pids, i);
	free(pids);
	return (result);
}

void	print_error_parsing(char *cmd_parse)
{
	ft_putendl_fd("minishell: failed command parsing", 2);
	free(cmd_parse);
	g_exit_status = 258;
}

int	execute_prompt(t_cmd_list *cmd_list, t_state *state)
{
	int	result;

	result = 0;
	state->cmd_parse = ft_strdup(state->cmd_line);
	cmd_list = parse(state->cmd_line, state);
	if (!cmd_list)
	{
		print_error_parsing(state->cmd_parse);
		return (1);
	}
	if (!is_full_of_space(state->cmd_parse) && !has_heredoc(cmd_list, state))
	{
		if (cmd_list->cmd_status == TYPE_SYNTAX_ERROR)
			print_error_syntax(cmd_list->head, TYPE_SYNTAX_ERROR);
		else if (cmd_list->cmd_status == TYPE_AMBIGUOUS_ERROR)
			print_error_syntax(cmd_list->head, TYPE_AMBIGUOUS_ERROR);
		else
			result = execute_cmd(cmd_list, state);
	}
	unlink_tmp_file(cmd_list);
	free_cmd_list(cmd_list);
	free(state->cmd_parse);
	add_history(state->cmd_line);
	return (result);
}

void	prompt(t_cmd_list *cmd_list, t_state *state)
{
	int	result;

	result = 0;
	while (1)
	{
		state->cmd_line = readline("minishell$ ");
		if (state->cmd_line)
		{
			if (state->cmd_line[0] != '\0')
				result = execute_prompt(cmd_list, state);
		}
		else
		{
			ft_putendl_fd("Ctrl+D exit", 1);
			g_exit_status = 0;
			break ;
		}
		free(state->cmd_line);
		state->cmd_line = NULL;
		if (result == 4242)
			return ;
	}
}
