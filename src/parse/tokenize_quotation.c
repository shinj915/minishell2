/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:55:54 by jishin            #+#    #+#             */
/*   Updated: 2025/04/13 19:21:19 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**extract_single_quotes(char *str, int start, int end)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * 4);
	if (!result)
		return (NULL);
	result[0] = ft_substr(str, 0, start);
	if (!result[0])
		return (free_2d_array(result));
	result[1] = ft_substr(str, start + 1, end - start - 1);
	if (!result[1])
		return (free_2d_array(result));
	result[2] = ft_substr(str, end + 1, ft_strlen(str));
	if (!result[2])
		return (free_2d_array(result));
	result[3] = NULL;
	return (result);
}

char	**extract_double_quotes(char *str, int start, int end, t_state *state)
{
	char	**result;

	(void)state;
	result = (char **)malloc(sizeof(char *) * 4);
	if (!result)
		return (NULL);
	result[0] = ft_substr(str, 0, start);
	if (!result[0])
		return (free_2d_array(result));
	result[1] = ft_substr(str, start + 1, end - start - 1);
	//result[1] = ft_tokenize_interpret_env_str(result[1], state);
	if (!result[1])
		return (free_2d_array(result));
	result[2] = ft_substr(str, end + 1, ft_strlen(str));
	if (!result[2])
		return (free_2d_array(result));
	result[3] = NULL;
	return (result);
}

char	**split_quotation(char *str, t_state *state)
{
	int		start;
	int		end;

	start = 0;
	while (str[start] && str[start] != '\'' && str[start] != '"')
		start++;
	if (str[start] == '\0')
		return (NULL);
	end = start;
	if (str[start] == '\'')
	{
		while (str[++end] && str[end] != '\'')
			;
		if (str[end] == '\'')
			return (extract_single_quotes(str, start, end));
	}
	if (str[start] == '"')
	{
		while (str[++end] && str[end] != '"')
			;
		if (str[end] == '"')
			return (extract_double_quotes(str, start, end, state));
	}
	return (NULL);
}

void	tokenize_quotation(t_token *token_list, t_state *state)
{
	char	**sep;

	(void)state;
	while (token_list != NULL)
	{
		if (token_list->token_type == TYPE_TOKEN_CHUNK)
		{
			sep = split_quotation(token_list->str, state);
			if (sep != NULL)
			{
				add_token(&token_list, 1, TYPE_TOKEN_CHUNK, sep[2]);
				add_token(&token_list, 1, TYPE_TOKEN_ARGV, sep[1]);
				free(token_list->str);
				token_list->str = ft_strdup(sep[0]);
				free_2d_array(sep);
				token_list = token_list->next;
			}
		}
		if (token_list)
			token_list = token_list->next;
	}
}
