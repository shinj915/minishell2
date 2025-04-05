/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_state_cmd_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:39:09 by jishin            #+#    #+#             */
/*   Updated: 2025/04/05 21:07:13 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_cmd_redir(t_cmd *cmd)
{
	t_cmd_redir	*ptr;

	while (cmd->redir_list != NULL)
	{
		if (cmd->redir_list->file != NULL)
			free(cmd->redir_list->file);
		ptr = cmd->redir_list;
		cmd->redir_list = cmd->redir_list->next;
		free(ptr);
	}
}

void	free_cmd_node(t_cmd_list *cmd_list)
{
	t_cmd	*ptr;

	if (cmd_list == NULL || cmd_list->head == NULL)
		return ;
	ptr = cmd_list->head;
	cmd_list->head = cmd_list->head->next;
	if (cmd_list->head != NULL)
		cmd_list->head->prev = NULL;
	if (cmd_list->head == NULL)
		cmd_list->tail = NULL;
	free_cmd_redir(ptr);
	if (ptr->exec_file_name != NULL)
		free(ptr->exec_file_name);
	if (ptr->argv != NULL)
		free_2d_array(ptr->argv);
	free(ptr);
}

void	*free_cmd_list(t_cmd_list *cmd_list)
{
	if (cmd_list == NULL)
		return (NULL);
	while (cmd_list->head != NULL)
		free_cmd_node(cmd_list);
	cmd_list->head = NULL;
	free(cmd_list);
	return (NULL);
}

void	free_state(t_state *state)
{
	t_env	*temp;

	rl_clear_history();
	while (state->env_list)
	{
		temp = state->env_list;
		free(state->env_list->key);
		free(state->env_list->value);
		state->env_list = state->env_list->next;
		free(temp);
	}
	free(state->env_list);
	free(state);
}
