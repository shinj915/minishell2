/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:33:30 by jishin            #+#    #+#             */
/*   Updated: 2025/04/23 16:20:41 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_command(t_cmd_list *cmd_list, t_state *state, int *result)
{
	state->cmd_parse = ft_strdup(state->cmd_line);
	cmd_list = parse(state->cmd_line, state);
	traverse_and_print(cmd_list);
	free_cmd_list(cmd_list);
	free(state->cmd_parse);
	add_history(state->cmd_line);
	*result = 1;
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
			g_exit_status = 130;
			break ;
		}
		free(state->cmd_line);
		state->cmd_line = NULL;
	}
}