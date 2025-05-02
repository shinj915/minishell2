/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:33:30 by jishin            #+#    #+#             */
/*   Updated: 2025/05/02 17:33:38 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_execute(t_cmd_list *cmd_list, t_state *state)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = get_envp(state->env_list);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		execve(cmd_list->head->exec_file_name, cmd_list->head->argv, envp);
		perror("execve failed");
		exit(1);
	}
	else
		waitpid(pid, &status, 0);
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
			write(2, "minishell: syntax error near unexpected token\n", 46);
			g_exit_status = 2;
		}
		else if (cmd_list->cmd_status == TYPE_AMBIGOUS_ERROR)
		{
			write(2, "minishell: ambiguous redirect\n", 30);
			g_exit_status = 1;
		}
		else
			*result = ft_execute(cmd_list, state);
	}
	*result = 1;
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