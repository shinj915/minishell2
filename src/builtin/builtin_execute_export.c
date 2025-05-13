/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:38:08 by eunam             #+#    #+#             */
/*   Updated: 2025/05/13 14:21:34 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(char *key)
{
	int	i;

	if (!key)
		return (0);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static t_env	*find_tail_env(t_env *env_list)
{
	t_env	*env;

	if (env_list == NULL)
		return (NULL);
	env = env_list;
	while (env->next != NULL)
		env = env->next;
	return (env);
}

static t_env	*ft_find_env(char *env_str, t_env *env_list)
{
	t_env	*env;
	char	*key;
	char	*value;

	if (!env_str)
		return (NULL);
	key = ft_substr(env_str, 0, ft_strchr(env_str, '=') - env_str);
	value = ft_strdup(ft_strchr(env_str, '=') + 1);
	env = ft_find_return_env(key, env_list);
	if (env)
	{
		free(env->value);
		env->value = value;
	}
	free(key);
	free(value);
	return (env);
}

static int	for_export_funtion(t_cmd *cmd, char *env_str, t_env *env_list)
{
	char	*key;
	char	*value;
	t_env	*tail;

	tail = find_tail_env(env_list);
	key = ft_substr(env_str, 0, ft_strchr(env_str, '=') - env_str);
	value = ft_strdup(ft_strchr(env_str, '=') + 1);
	if (!is_valid_key(key))
	{
		print_error_builtin(cmd, env_str, ERROR_INVALID_IDENTIFIER);
		free(key);
		free(value);
		return (1);
	}
	tail = add_env(tail, key, value);
	return (0);
}

int	builtin_execute_export(t_cmd *cmd, t_state *state)
{
	int		i;
	int		argc;
	int		res;

	i = 1;
	res = 0;
	argc = find_argc(cmd->argv);
	if (argc < 2)
	{
		print_error_builtin(cmd, NULL, ERROR_TOO_FEW_ARGS);
		return (1);
	}
	while (i < argc)
	{
		if (ft_strchr(cmd->argv[i], '='))
		{
			if (!ft_find_env(cmd->argv[i], state->env_list))
				res += for_export_funtion(cmd, cmd->argv[i], state->env_list);
		}
		i++;
	}
	if (res > 0)
		return (1);
	else
		return (0);
}
