/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:33:30 by jishin            #+#    #+#             */
/*   Updated: 2025/05/28 19:47:39 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	get_cmd_exit_code(t_cmd *cmd, t_state *state, pid_t *pid)
{
	int	result;

	result = check_pipe(&cmd);
	if (result > 0)
		return (result);
	*pid = -1;
	if (is_exit(cmd) && cmd->prev == NULL && cmd->next == NULL)
		result = execute_single_exit(cmd, state);
	else if (is_builtin_command(cmd) && cmd->prev == NULL && cmd->next == NULL)
	{
		if (set_redirection(cmd))
			return (1);
		result = ft_exec_builtin(cmd, state);
	}
	else
		execute_child_processes(cmd, state, pid);
	return (result);
}

static int	loop_cmd_list(t_cmd **cmd, t_state *state, pid_t *pids, int *i)
{
	int	result;

	result = 0;
	while ((*cmd) != NULL)
	{
		if ((*cmd)->argv == NULL || (*cmd)->argv[0] == NULL || \
			(*cmd)->argv[0][0] == '\0')
		{
			if (!(*cmd)->redir_list)
				ft_putendl_fd("minishell: : command not found", 2);
			set_redirection(*cmd);
			pids[*i] = -1;
			(*i)++;
			(*cmd) = (*cmd)->next;
			continue ;
		}
		result = get_cmd_exit_code(*cmd, state, &pids[*i]);
		(*cmd) = (*cmd)->next;
		(*i)++;
	}
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
	if (!set_pids(state, &pids))
		return (1);
	cmd = cmd_list->head;
	result = loop_cmd_list(&cmd, state, pids, &i);
	wait_for_processes(state, pids, i);
	free(pids);
	return (result);
}

static int	execute_prompt(t_state *state)
{
	int			result;
	t_cmd_list	*cmd_list;

	result = 0;
	cmd_list = parse(state->cmd_line, state);
	state->cmd_list = cmd_list;
	if (!is_full_of_space(state->cmd_line) && !has_heredoc(cmd_list, state))
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
	add_history(state->cmd_line);
	return (result);
}

void	prompt(t_state *state)
{
	int	result;

	result = 0;
	while (1)
	{
		state->cmd_line = readline("minishell$ ");
		if (state->cmd_line)
		{
			if (state->cmd_line[0] != '\0')
				result = execute_prompt(state);
		}
		else
		{
			ft_putendl_fd("Ctrl+D exit", 1);
			g_exit_status = 0;
			break ;
		}
		free(state->cmd_line);
		state->cmd_line = NULL;
		if (result == EXIT_MINISHELL)
			return ;
	}
}
