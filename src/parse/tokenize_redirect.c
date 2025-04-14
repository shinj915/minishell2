/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:37:56 by jishin            #+#    #+#             */
/*   Updated: 2025/04/14 15:25:56 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	retokenize_single_redirect(t_token *token, int idx)
{
	char	*str;
	char	*single_redir;
	char	*remainer;

	str = token->str;
	single_redir = ft_substr(str, 0, 1);
	remainer = ft_substr(str, idx, ft_strlen(str));
	if (!single_redir || !remainer)
		return ;
	token->str = single_redir;
	if (token->str[0] == '<')
		token->token_type = TYPE_TOKEN_IO_L;
	else if (token->str[0] == '>')
		token->token_type = TYPE_TOKEN_IO_R;
	add_token(&token, 1, TYPE_TOKEN_CHUNK, remainer);
	free_multiple_array(str, remainer, NULL, NULL);
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
			retokenize_single_redirect(token, 1);
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
	delete_empty_token(&ptr);
	retokenize_heredoc(ptr);
	retokenize_appending_output(ptr);
}
