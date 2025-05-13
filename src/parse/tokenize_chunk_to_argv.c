/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_chunk_to_argv.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:38:34 by jishin            #+#    #+#             */
/*   Updated: 2025/04/23 16:11:37 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	merge_two_argv_tokens(t_token *token, t_token *ptr, char *str)
{
	if (token->str[0] == '$' && token->str[1] == '\0')
	{
		free(token->str);
		token->str = ft_strdup("");
	}
	str = ft_strjoin(token->str, token->next->str);
	if (!str)
		return (0);
	if (str[0] != '\0')
		token->is_null = TYPE_INITIAL_STATUS;
	ptr = token->next;
	free(token->str);
	token->str = str;
	token->next = token->next->next;
	free_token(ptr);
	return (1);
}

static int	merge_consecutive_argv_tokens(t_token *token)
{
	t_token	*ptr;
	char	*str;
	int		merge_flag;

	merge_flag = 0;
	while (token != NULL)
	{
		if (token->token_type == TYPE_TOKEN_ARGV && token->next && \
			token->next->token_type == TYPE_TOKEN_ARGV)
		{
			ptr = NULL;
			str = NULL;
			if (!merge_two_argv_tokens(token, ptr, str))
				return (merge_flag);
			merge_flag = 1;
		}
		else
			token = token->next;
	}
	return (merge_flag);
}

void	tokenize_chunk_to_argv(t_token *token_list)
{
	t_token	*next;
	t_token	*ptr;
	int		merged_flag;

	ptr = token_list;
	while (token_list != NULL)
	{
		next = token_list->next;
		if (token_list->token_type == TYPE_TOKEN_CHUNK)
			token_list->token_type = TYPE_TOKEN_ARGV;
		token_list = next;
	}
	while (1)
	{
		merged_flag = merge_consecutive_argv_tokens(ptr);
		if (!merged_flag)
			break ;
	}
}
