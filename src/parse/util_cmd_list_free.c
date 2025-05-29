/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cmd_list_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:48:43 by jishin            #+#    #+#             */
/*   Updated: 2025/05/28 16:23:17 by jishin           ###   ########.fr       */
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

void	free_cmd_node(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_cmd_redir(cmd);
	if (cmd->exec_file_name != NULL)
		free(cmd->exec_file_name);
	if (cmd->argv != NULL)
		free_2d_array(cmd->argv);
	free(cmd);
}

void	*free_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd	*cur;
	t_cmd	*next;

	if (cmd_list == NULL)
		return (NULL);
	cur = cmd_list->head;
	while (cur)
	{
		next = cur->next;
		free_cmd_node(cur);
		cur = next;
	}
	cmd_list->head = NULL;
	free(cmd_list);
	return (NULL);
}
