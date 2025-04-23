/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_env_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:31:55 by jishin            #+#    #+#             */
/*   Updated: 2025/04/23 16:11:40 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	expand_dollar_question(t_token *token)
{
	char	*str;
	char	*exit_status;
	char	*remainer;
	char	*result;

	str = token->str;
	exit_status = ft_itoa(g_exit_status);
	remainer = ft_substr(str, 2, ft_strlen(str));
	if (!exit_status || !remainer)
	{
		free_multiple_array(exit_status, remainer, NULL, NULL);
		return ;
	}
	result = ft_strjoin(exit_status, remainer);
	free_multiple_array(exit_status, remainer, NULL, NULL);
	if (!result)
		return ;
	free(token->str);
	token->str = result;
}

static char	*set_env_null(t_token *token)
{
	token->is_null = TYPE_ARGV_NULL;
	return ("");
}

static void	expand_env_var_token(t_token *token, int idx, t_state *state)
{
	char	*str;
	char	*key;
	char	*value;
	char	*remainer;

	str = token->str;
	while (str[idx] == '_' || ft_isalnum(str[idx]))
		idx++;
	key = ft_substr(str, 1, idx - 1);
	token->origin_str = ft_strjoin("$", key);
	if (!key)
		return ;
	value = ft_getenv(state, key);
	if (value == NULL)
		value = set_env_null(token);
	free(key);
	value = ft_strdup(value);
	if (!value)
		return ;
	remainer = ft_substr(str, idx, ft_strlen(str));
	token->str = value;
	token->token_type = TYPE_TOKEN_ARGV;
	add_token(&token, 1, TYPE_TOKEN_CHUNK, remainer);
	free_multiple_array(str, remainer, NULL, NULL);
	retokenize_expanded_token(token);
}

static void	handle_env_var(t_token *token, t_state *state)
{
	t_token	*next;
	char	**split;
	int		idx;

	split = parse_split(token->str, '$');
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
		if (token->str[0] == '$' && \
			(token->str[1] == '_' || ft_isalpha(token->str[1])))
			expand_env_var_token(token, 1, state);
		else if (token->str[0] == '$' && token->str[1] == '?')
			expand_dollar_question(token);
		token = next;
	}
}

void	tokenize_env_var(t_token *token_list, t_state *state)
{
	t_token	*next;

	while (token_list != NULL)
	{
		next = token_list->next;
		if (token_list->token_type == TYPE_TOKEN_CHUNK)
			handle_env_var(token_list, state);
		token_list = next;
	}
}
