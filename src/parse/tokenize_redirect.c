/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:37:56 by jishin            #+#    #+#             */
/*   Updated: 2025/04/14 13:45:40 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_detach_sign(t_token *token, int idx)
{
	char	*sign;
	char	*tmp;
	char	*tmp2;

	tmp = token->str;
	sign = ft_substr(tmp, 0, 1);
	tmp2 = ft_substr(tmp, idx, ft_strlen(tmp));
	if (!sign || !tmp2)
		return ;
	token->str = sign;
	if (token->str[0] == '<')
		token->token_type = TYPE_TOKEN_IO_L;
	else if (token->str[0] == '>')
		token->token_type = TYPE_TOKEN_IO_R;
	add_token(&token, 1, TYPE_TOKEN_CHUNK, tmp2);
	free_multiple_array(tmp, tmp2, NULL, NULL);
}

static void	retokenize_heredoc(t_token *token)
{
	t_token	*ptr;
	char	*str;

	while (token != NULL)
	{
		if (token->token_type == TYPE_TOKEN_IO_L && token->next \
		&& token->next->token_type == TYPE_TOKEN_IO_L)
		{
			str = ft_strdup("<<");
			if (!str)
				return ;
			ptr = token->next;
			token->next = token->next->next;
			free(token->str);
			token->str = str;
			token->token_type = TYPE_TOKEN_IO_LL;
			free_token(ptr);
		}
		token = token->next;
	}
}

static void	retokenize_appending_output(t_token *token)
{
	t_token	*ptr;
	char	*str;

	while (token != NULL)
	{
		if (token->token_type == TYPE_TOKEN_IO_R && token->next \
		&& token->next->token_type == TYPE_TOKEN_IO_R)
		{
			str = ft_strdup(">>");
			if (!str)
				return ;
			ptr = token->next;
			token->next = token->next->next;
			free(token->str);
			token->str = str;
			token->token_type = TYPE_TOKEN_IO_RR;
			free_token(ptr);
		}
		token = token->next;
	}
}


static void	split_redirect_token(t_token *token)
{
	t_token	*next;
	char	**split;
	int		idx;

	split = split_with_two_delim(token->str, '<', '>');
	if (!split)
		return ;
	free(token->str);
	token->str = ft_strdup(split[0]);
	idx = 0;
	while (split[++idx] != NULL)
		add_token(&token, idx, token->token_type, split[idx]);
	free_2d_array(split);
	while (--idx >= 0 && token != NULL)
	{
		next = token->next;
		if (token->str[0] == '<' || token->str[0] == '>')
			ft_detach_sign(token, 1);
		token = next;
	}
}

void	tokenize_redirect(t_token *token_list)
{
	t_token	*next;
	t_token	*ptr;

	ptr = token_list;
	while (token_list != NULL)
	{
		next = token_list->next;
		if (token_list->token_type == TYPE_TOKEN_CHUNK)
			split_redirect_token(token_list);
		token_list = next;
	}
	retokenize_heredoc(ptr);
	retokenize_appending_output(ptr);
}
