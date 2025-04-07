/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:31:24 by jishin            #+#    #+#             */
/*   Updated: 2025/04/07 11:34:41 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_full_of_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] != ' ' && cmd[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static void	prompt_excute(t_cmd_list *cmd_list, t_state *state, int *result)
{
	state->cmd_parse = ft_strdup(state->cmd_line);
	cmd_list = ft_parse(state->cmd_parse, state);
	if (!is_full_of_space(state->cmd_parse) /*&& !ft_heredoc(cmd_list, state)*/)
	{
		if (cmd_list->cmd_status == TYPE_SYNTAX_ERROR)
		{
			printf("minishell: syntax error near unexpected token '%s'\n", \
					cmd_list->head->exec_file_name);
			g_exit_status = 1;
		}
		else if (cmd_list->cmd_status == TYPE_AMBIGOUS_ERROR)
		{
			printf("minishell: %s: ambiguous redirect\n", \
					cmd_list->head->exec_file_name);
			g_exit_status = 1;
		}
		//else
		//	*result = ft_execute(cmd_list, state);
	}
	//unlink_tmp_file(cmd_list);
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
				prompt_excute(cmd_list, state, &result);
		}
		else
		{
			printf("Ctrl+D exit\n");
			g_exit_status = 130;
			break ;
		}
		free(state->cmd_line);
		state->cmd_line = NULL;
		if (result == 4242)
			return ;
	}
}
