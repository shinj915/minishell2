/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:32:15 by jishin            #+#    #+#             */
/*   Updated: 2025/05/28 19:47:55 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_child_process(t_state *state, char **envp, int exit_code)
{
	free(state->pids);
	free_cmd_list(state->cmd_list);
	free_state(state);
	free_2d_array(envp);
	exit(exit_code);
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

int	is_exit(t_cmd *cmd)
{
	if (strcmp(cmd->exec_file_name, "exit") == 0)
		return (1);
	return (0);
}

int	set_pids(t_state *state, pid_t **pids)
{
	t_cmd	*cmd_ptr;
	int		cmd_count;

	cmd_count = 0;
	cmd_ptr = state->cmd_list->head;
	while (cmd_ptr != NULL)
	{
		cmd_count++;
		cmd_ptr = cmd_ptr->next;
	}
	*pids = malloc(sizeof(pid_t) * (cmd_count));
	if (!*pids)
		return (0);
	state->pids = *pids;
	return (1);
}

void	wait_for_processes(t_state *state, pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] > 0)
		{
			signal(SIGINT, SIG_IGN);
			waitpid(pids[i], &status, 0);
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				state->exit_signal = 1;
				write(1, "\n", 1);
				last_status = 128 + WTERMSIG(status);
			}
			g_exit_status = last_status;
		}
		i++;
	}
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
}
