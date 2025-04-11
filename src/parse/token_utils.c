/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:23:13 by jishin            #+#    #+#             */
/*   Updated: 2025/04/11 14:23:43 by jishin           ###   ########.fr       */
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
