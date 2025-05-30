/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:38:08 by eunam             #+#    #+#             */
/*   Updated: 2025/05/30 10:50:36 by jishin           ###   ########.fr       */
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

static void	print_export_envs(t_cmd *cmd, t_env *env_list)
{
	t_env	*env;

	env = env_list;
	while (env)
	{
		ft_putstr_fd("declare -x ", cmd->fd_out);
		if (env->value)
		{
			ft_putstr_fd(env->key, cmd->fd_out);
			ft_putstr_fd("=\"", cmd->fd_out);
			ft_putstr_fd(env->value, cmd->fd_out);
			ft_putendl_fd("\"", cmd->fd_out);
		}
		else
			ft_putendl_fd(env->key, cmd->fd_out);
		env = env->next;
	}
}

static int	make_env(t_cmd *cmd, int i, t_env *env_list)
{
	int		res;
	t_env	*env;

	res = 0;
	if (ft_strchr(cmd->argv[i], '='))
	{
		if (!ft_find_env(cmd->argv[i], env_list))
			res += for_export_funtion(cmd, cmd->argv[i], env_list);
	}
	else
	{
		env = ft_find_return_env(cmd->argv[i], env_list);
		if (!env)
		{
			if (!is_valid_key(cmd->argv[i]))
			{
				print_error_builtin(cmd, cmd->argv[i], \
									ERROR_INVALID_IDENTIFIER);
				return (1);
			}
			add_nullvalue_env(cmd->argv[i], env_list);
		}
	}
	return (res);
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
		print_export_envs(cmd, state->env_list);
	while (i < argc)
	{
		res += make_env(cmd, i, state->env_list);
		i++;
	}
	if (res > 0)
		return (1);
	else
		return (0);
}
