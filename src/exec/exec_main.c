/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:33:30 by jishin            #+#    #+#             */
/*   Updated: 2025/05/05 15:03:59 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	execute_external_cmd(t_cmd *cmd, t_state *state)
{
	pid_t		pid;
	int			status;
	char		*path;
	char		**envp;
	struct stat	st;

	path = NULL;
	envp = get_envp(state->env_list);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
		path = cmd->exec_file_name;
		if (ft_strchr(cmd->exec_file_name, '/'))
		{
			if (stat(cmd->exec_file_name, &st) == 0 && S_ISDIR(st.st_mode))
				print_error_external(cmd, ERROR_ISDIR);
			if (access(cmd->exec_file_name, X_OK))
				print_error_external(cmd, ERROR_NORMAL);
		}
		else
			path = get_exec_path(cmd, state);
		if (!path)
			print_error_external(cmd, ERROR_CMD_NOT_FOUND);
		execve(path, cmd->argv, envp);
		perror("minishell: execve failed");
		exit(127);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		g_exit_status = WEXITSTATUS(status);
		signal(SIGINT, ft_sigint);
	}
	free_2d_array(envp);
	return (WEXITSTATUS(status));
}

int	execute_cmd(t_cmd_list *cmd_list, t_state *state)
{
	t_cmd	*cmd;
	int		result;

	cmd = cmd_list->head;
	result = 0;
	while (cmd != NULL)
	{
		result = execute_external_cmd(cmd, state);
		cmd = cmd->next;
	}
	return (result);
}

int	is_full_of_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	execute_prompt(t_cmd_list *cmd_list, t_state *state, int *result)
{
	state->cmd_parse = ft_strdup(state->cmd_line);
	cmd_list = parse(state->cmd_line, state);
	if (cmd_list && !is_full_of_space(state->cmd_parse))
	{
		if (cmd_list->cmd_status == TYPE_SYNTAX_ERROR)
			print_error_syntax(cmd_list->head, TYPE_SYNTAX_ERROR);
		else if (cmd_list->cmd_status == TYPE_AMBIGUOUS_ERROR)
			print_error_syntax(cmd_list->head, TYPE_AMBIGUOUS_ERROR);
		else
			*result = execute_cmd(cmd_list, state);
	}
	free_cmd_list(cmd_list);
	free(state->cmd_parse);
	add_history(state->cmd_line);
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
				execute_prompt(cmd_list, state, &result);
		}
		else
		{
			write(1, "Ctrl+D exit\n", 12);
			g_exit_status = 0;
			break ;
		}
		free(state->cmd_line);
		state->cmd_line = NULL;
	}
}