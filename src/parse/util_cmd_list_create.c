/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cmd_list_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:44:21 by jishin            #+#    #+#             */
/*   Updated: 2025/05/01 13:40:22 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd_list	*create_cmd_list(void)
{
	t_cmd_list	*result;

	result = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!result)
		return (NULL);
	result->head = NULL;
	result->tail = NULL;
	result->cmd_status = 0;
	return (result);
}

t_cmd	*create_cmd(void)
{
	t_cmd	*result;
	char	**argv;

	result = (t_cmd *)malloc(sizeof(t_cmd));
	if (!result)
		return (NULL);
	argv = (char **)malloc(sizeof(char *));
	if (!argv)
	{
		free (result);
		return (NULL);
	}
	argv[0] = NULL;
	result->argv = argv;
	result->exec_file_name = NULL;
	result->pipe_fd[0] = -1;
	result->pipe_fd[1] = -1;
	result->redir_fd_in = 0;
	result->redir_fd_out = 1;
	result->cmd_type = 0;
	result->redir_list = NULL;
	result->prev = NULL;
	result->next = NULL;
	return (result);
}

t_cmd	*add_cmd_to_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd	*new;
	t_cmd	*prev_node;

	if (!cmd_list)
		return (NULL);
	new = create_cmd();
	if (!new)
		return (NULL);
	if (cmd_list->head == NULL)
	{
		cmd_list->head = new;
		new->prev = NULL;
		return (new);
	}
	prev_node = cmd_list->head;
	while (prev_node->next != NULL)
		prev_node = prev_node->next;
	prev_node->next = new;
	new->prev = prev_node;
	cmd_list->tail = new;
	return (new);
}

t_cmd_redir	*add_cmd_redir(t_cmd *cmd, int type, char *file)
{
	t_cmd_redir	*result;
	t_cmd_redir	*prev;
	char		*str;

	result = (t_cmd_redir *)malloc(sizeof(t_cmd_redir));
	str = ft_strdup(file);
	if (!result || str == NULL)
		return (free_multiple_array(result, str, NULL, NULL));
	result->file = str;
	result->redir_type = type;
	result->next = NULL;
	if (cmd->redir_list == NULL)
		cmd->redir_list = result;
	else
	{
		prev = cmd->redir_list;
		while (prev->next != NULL)
			prev = prev->next;
		prev->next = result;
	}
	return (result);
}

void	*add_cmd_argv(t_cmd *cmd, char *str, int idx)
{
	char	**new_argv;
	char	*new_str;
	int		i;

	i = -1;
	if (idx == 0)
	{
		new_str = ft_strdup(str);
		if (new_str == NULL)
			return (NULL);
		cmd->exec_file_name = new_str;
	}
	new_str = ft_strdup(str);
	while (cmd->argv[++i] != NULL)
		;
	new_argv = (char **)malloc(sizeof(char *) * (i + 2));
	if (new_argv == NULL || new_str == NULL)
		return (free_multiple_array(new_argv, new_str, NULL, NULL));
	new_argv[i] = new_str;
	new_argv[i + 1] = NULL;
	while ((--i) >= 0)
		new_argv[i] = cmd->argv[i];
	free(cmd->argv);
	cmd->argv = new_argv;
	return (NULL);
}
