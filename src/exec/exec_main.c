/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:33:30 by jishin            #+#    #+#             */
/*   Updated: 2025/05/13 15:55:44 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	get_cmd_exit_code(t_cmd *cmd, t_state *state, pid_t *pid)
{
	
	int	result;

	result = check_pipe_and_cmd(&cmd);
	if (result > 0)
		return (result);
	if (is_exit(cmd) && cmd->prev == NULL && cmd->next == NULL)
		result = execute_single_exit(cmd, state);
	else if (is_builtin_command(cmd) && cmd->prev == NULL && cmd->next == NULL)
	{
		*pid = -1;
		if (set_redirection(cmd))
			return (1);
		result = ft_exec_builtin(cmd, state);
	}
	else
		execute_child_processes(cmd, state, pid);
	return (result);
}

static int	execute_cmd(t_cmd_list *cmd_list, t_state *state)
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
		if (result != 0)
		{
			free(pids);
			return (result);
		}
		cmd = cmd->next;
		i++;
	}
	wait_for_processes(pids, i);
	free(pids);
	return (result);
}

static int	execute_prompt(t_cmd_list *cmd_list, t_state *state)
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
		if (result != 0 && result != 4242)
			g_exit_status = result;
		if (result == 4242)
			return ;
	}
}
