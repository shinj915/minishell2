/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:22:31 by jishin            #+#    #+#             */
/*   Updated: 2025/05/19 13:40:09 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_state(t_state *state)
{
	t_env	*ptr;

	rl_clear_history();
	while (state->env_list)
	{
		ptr = state->env_list;
		free(state->env_list->key);
		free(state->env_list->value);
		state->env_list = state->env_list->next;
		free(ptr);
	}
	free(state);
}

void	unlink_tmp_file(t_cmd_list *cmd_lists)
{
	t_cmd			*cmd;
	t_cmd_redir		*red;

	if (!cmd_lists)
		return ;
	cmd = cmd_lists->head;
	while (cmd != NULL)
	{
		red = cmd->redir_list;
		while (red != NULL)
		{
			if (red->redir_type == TYPE_AFTER_HEREDOC)
				unlink(red->file);
			red = red->next;
		}		
		cmd = cmd->next;
	}
}
