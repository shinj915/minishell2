/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quotation_util.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:56:39 by jishin            #+#    #+#             */
/*   Updated: 2025/04/14 00:08:05 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_dollar_question(char *str)
{
	char	*exit_status;
	char	*remainer;
	char	*result;

	if (str[1] != '?')
		return (str);
	exit_status = ft_itoa(g_exit_status);
	remainer = ft_substr(str, 2, ft_strlen(str));
	if (!exit_status || !remainer)
	{
		free_multiple_array(exit_status, remainer, NULL, NULL);
		return (str);
	}
	result = ft_strjoin(exit_status, remainer);
	free_multiple_array(exit_status, remainer, NULL, NULL);
	if (!result)
		return (str);
	free(str);
	return (result);
}

char	*expand_env_in_str(char *str, int idx, t_state *state)
{
	char	*key;
	char	*value;

	if (str[++idx] != '_' && !ft_isalpha(str[idx]))
		return (expand_dollar_question(str));
	while (str[idx] == '_' || ft_isalnum(str[idx]))
		idx++;
	key = ft_substr(str, 1, idx - 1);
	if (!key)
		return (str);
	value = ft_getenv(state, key);
	free(key);
	if (!value)
		value = "";
	key = ft_substr(str, idx, ft_strlen(str));
	value = ft_strjoin(value, key);
	free(key);
	if (!value)
		return (str);
	free(str);
	return (value);
}

char	*handle_double_quoted_sequence(char *str, t_state *state)
{
	char	**split;
	char	*result;
	char	*ptr_result;
	char	*env;
	int		idx;

	split = parse_split(str, '$');
	if (!split)
		return (str);
	idx = -1;
	result = ft_strdup("");
	while (split[++idx] != NULL && result != NULL)
	{
		env = ft_strdup(split[idx]);
		if (env[0] == '$')
			env = expand_env_in_str(env, 0, state);
		ptr_result = result;
		result = ft_strjoin(result, env);
		free_multiple_array(ptr_result, env, NULL, NULL);
	}
	free_2d_array(split);
	if (!result)
		return (str);
	free(str);
	return (result);
}
