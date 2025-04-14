/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:54:27 by jishin            #+#    #+#             */
/*   Updated: 2025/04/14 10:23:23 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_str_only_space(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

static void	retokenize_space_token(t_token *token_list)
{
	while (token_list != NULL)
	{
		if (check_str_only_space(token_list->str) && \
			token_list->token_type == TYPE_TOKEN_CHUNK)
		{
			free(token_list->str);
			token_list->str = ft_strdup(" ");
			token_list->token_type = TYPE_TOKEN_SPACE;
		}
		token_list = token_list->next;
	}
}

static void	split_space_token(t_token *token)
{
	t_token	*ptr;
	char	**split;
	char	*str;
	int		idx;

	split = split_with_delim(token->str, ' ');
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

void	tokenize_space(t_token *token_list)
{
	t_token	*next;
	t_token	*ptr;

	ptr = token_list;
	while (ptr != NULL)
	{
		next = ptr->next;
		if (ptr->token_type == TYPE_TOKEN_CHUNK)
			split_space_token(ptr);
		ptr = next;
	}
	retokenize_space_token(token_list);
}
