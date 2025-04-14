/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:23:13 by jishin            #+#    #+#             */
/*   Updated: 2025/04/14 15:26:46 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*create_token(int token_type, const char *str)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token_type = token_type;
	new_token->is_null = TYPE_INITIAL_STATUS;
	new_token->str = ft_strdup(str);
	if (!new_token->str)
		return (NULL);
	new_token->origin_str = NULL;
	new_token->next = NULL;
	return (new_token);
}

static t_token	*add_token_at_head(t_token **token_list, t_token *new_token)
{
	new_token->next = *token_list;
	*token_list = new_token;
	return (new_token);
}

t_token	*add_token(t_token **token_list, size_t idx, int type, char *str)
{
	t_token	*new_token;
	t_token	*prev;
	t_token	*current;

	if (!token_list)
		return (NULL);
	new_token = create_token(type, str);
	if (!new_token)
		return (NULL);
	if (idx == 0 || *token_list == NULL)
		return (add_token_at_head(token_list, new_token));
	current = *token_list;
	prev = NULL;
	while (current != NULL && idx > 0)
	{
		prev = current;
		current = current->next;
		idx--;
	}
	new_token->next = current;
	if (prev != NULL)
		prev->next = new_token;
	return (new_token);
}

void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->str != NULL)
		free(token->str);
	if (token->origin_str != NULL)
		free(token->origin_str);
	free(token);
}

void	free_token_list(t_token *token_list)
{
	t_token	*ptr;

	ptr = token_list;
	while (ptr != NULL)
	{
		if (ptr->str != NULL)
			free(ptr->str);
		if (ptr->origin_str != NULL)
			free(ptr->origin_str);
		token_list = ptr;
		ptr = ptr->next;
		free(token_list);
	}
}
