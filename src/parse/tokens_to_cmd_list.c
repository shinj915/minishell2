/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmd_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:07:44 by jishin            #+#    #+#             */
/*   Updated: 2025/04/17 13:17:34 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*interpret_tokens(t_token *t, t_cmd **cmd, t_cmd_list *result, int *idx)
{
	if (t->token_type == TYPE_TOKEN_PIPE)
	{
		(*cmd) = add_cmd_to_cmd_list(result);
		if ((*cmd) == NULL)
			return (free_cmd_list(result));
		(*idx) = -1;
	}
	if (t->token_type == TYPE_TOKEN_ARGV
		&& ((++(*idx) == 0) || t->is_null != TYPE_ARGV_NULL))
		add_cmd_argv((*cmd), t->str, (*idx));
	if (t->token_type >= TYPE_TOKEN_IO_L && \
		t->token_type <= TYPE_TOKEN_IO_RR)
	{
		if (t->token_type == TYPE_TOKEN_IO_LL
			&& t->next->origin_str != NULL)
			add_cmd_redir((*cmd), t->token_type, t->next->origin_str);
		else
			add_cmd_redir((*cmd), t->token_type, t->next->str);
		t = t->next;
	}
	t = t->next;
	return (t);
}

t_cmd_list	*tokens_to_cmd_list(t_token *token_list)
{
	t_cmd_list	*result;
	t_cmd		*cmd;
	int			idx;

	result = create_cmd_list();
	if (!result)
		return (NULL);
	cmd = add_cmd_to_cmd_list(result);
	if (!cmd)
		return (NULL);
	idx = -1;
	while (token_list != NULL)
		token_list = interpret_tokens(token_list, &cmd, result, &idx);
	return (result);
}