/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunam <eunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:38:08 by eunam             #+#    #+#             */
/*   Updated: 2025/05/08 14:38:08 by eunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_valid_key(char *key)
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

static t_env	*for_export_funtion(t_cmd *cmd, t_env *tail, char *env_str)
{
	char	*key;
	char	*value;

	if (!env_str)
		return (NULL);
	key = ft_substr(env_str, 0, ft_strchr(env_str, '=') - env_str);
	value = ft_strdup(ft_strchr(env_str, '=') + 1);
	if (!is_valid_key(key))
	{
		print_error(cmd, env_str, ERROR_INVALID_IDENTIFIER);
		free(key);
		free(value);
		return (tail);
	}
	tail = add_env(tail, key, value);
	// free(key);
	// free(value); // double free
	return (tail);
}

int builtin_execute_export(t_cmd *cmd, t_state *state)
{
	int		i;
	int		argc;
	t_env	*tail;

	i = 1;
	argc = find_argc(cmd->argv);
	if (argc < 2)
		return (builtin_execute_env(cmd, state));
	tail = find_tail_env(state->env_list);
	while (i < argc)
	{
		if (ft_strchr(cmd->argv[i], '='))
		{
			if (!ft_find_env(cmd->argv[i], state->env_list))
				tail = for_export_funtion(cmd, tail, cmd->argv[i]);
		}
		i++;
	}
	return (0);
}
