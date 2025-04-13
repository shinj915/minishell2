/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_in_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:56:39 by jishin            #+#    #+#             */
/*   Updated: 2025/04/13 21:43:22 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_dollar_question(char *str)
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
	char	*env;

	if (str[++idx] != '_' && !ft_isalpha(str[idx]))
		return (expand_dollar_question(str));
	while (str[idx] == '_' || ft_isalnum(str[idx]))
		idx++;
	key = ft_substr(str, 1, idx - 1);
	if (!key)
		return (str);
	env = ft_getenv(state, key);
	free(key);
	if (!env)
		env = "";
	key = ft_substr(str, idx, ft_strlen(str));
	env = ft_strjoin(env, key);
	free(key);
	if (!env)
		return (str);
	free(str);
	return (env);
}

char	*handle_double_quoted_sequence(char *str, t_state *state)
{
	char	**split;
	char	*result;
	char	*ptr_result;
	char	*env;
	int		i;

	split = parse_split(str, '$');
	if (!split)
		return (str);
	i = -1;
	result = ft_strdup("");
	while (split[++i] != NULL && result != NULL)
	{
		env = ft_strdup(split[i]);
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
