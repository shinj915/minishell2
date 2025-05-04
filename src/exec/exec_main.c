/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:33:30 by jishin            #+#    #+#             */
/*   Updated: 2025/05/04 16:37:08 by jishin           ###   ########.fr       */
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

int	ft_execute(t_cmd_list *cmd_list, t_state *state)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**envp;

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
		if (ft_strchr(cmd_list->head->exec_file_name, '/'))
		{
			if (access(cmd_list->head->exec_file_name, X_OK) == 0)
				path = ft_strdup(cmd_list->head->exec_file_name);
		}
		else
			path = get_exec_path(cmd_list->head, state);
		if (!path)
		{
			ft_putendl_fd("minishell: command not found", 2);
			free_2d_array(envp);
			return (127);
		}
		execve(path, cmd_list->head->argv, envp);
		perror("execve failed");
		exit(127);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, ft_sigint);
	}
	free_2d_array(envp);
	return (WEXITSTATUS(status));
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

void	execute_command(t_cmd_list *cmd_list, t_state *state, int *result)
{
	state->cmd_parse = ft_strdup(state->cmd_line);
	cmd_list = parse(state->cmd_line, state);
	if (cmd_list && !is_full_of_space(state->cmd_parse))
	{
		if (cmd_list->cmd_status == TYPE_SYNTAX_ERROR)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token\n", 2);
			g_exit_status = 2;
		}
		else if (cmd_list->cmd_status == TYPE_AMBIGOUS_ERROR)
		{
			ft_putendl_fd("minishell: ambiguous redirect\n", 2);
			g_exit_status = 1;
		}
		else
			*result = ft_execute(cmd_list, state);
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
				execute_command(cmd_list, state, &result);
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