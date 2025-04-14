/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:38:01 by jishin            #+#    #+#             */
/*   Updated: 2025/04/14 12:48:32 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_pipe_one(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	if (count == 1)
		return (1);
	else
		return (0);
}

static void	retokenize_pipe_token(t_token *token_list)
{
	t_token	*ptr;

	while (token_list != NULL)
	{
		if (check_pipe_one(token_list->str) && \
			token_list->token_type == TYPE_TOKEN_CHUNK)
		{
			ptr = add_token(&token_list, 1, TYPE_TOKEN_CHUNK, \
							(token_list->str) + 1);
			if (!ptr)
				return ;
			free(token_list->str);
			token_list->str = ft_strdup("|");
			if (!token_list->str)
				return ;
			token_list->token_type = TYPE_TOKEN_PIPE;
		}
		token_list = token_list->next;
	}
}

static void	split_pipe_token(t_token *token)
{
	t_token	*ptr;
	char	**split;
	char	*str;
	int		idx;

	split = parse_split(token->str, '|');
	if (!split || !split[0])
		return ;
	str = ft_strdup(split[0]);
	if (str == NULL)
	{
		free_2d_array(split);
		return ;
	}
	free(token->str);
	token->str = str;
	ptr = token;
	idx = 0;
	while (split[++idx] != NULL && ptr != NULL)
		ptr = add_token(&token, idx, TYPE_TOKEN_CHUNK, split[idx]);
	free_2d_array(split);
}

void	tokenize_pipe(t_token *token_list)
{
	t_token	*next;
	t_token	*ptr;

	ptr = token_list;
	while (ptr != NULL)
	{
		next = ptr->next;
		if (ptr->token_type == TYPE_TOKEN_CHUNK)
			split_pipe_token(ptr);
		ptr = next;
	}
	retokenize_pipe_token(token_list);
}
