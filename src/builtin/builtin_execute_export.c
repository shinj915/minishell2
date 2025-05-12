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
// export_env_vals
static int	export_new_env(t_cmd *cmd, char *env_str, t_env *env_list)
{
	char	*key;
	char	*value;
	char	*temp;
	t_env	*tail;

	tail = find_tail_env(env_list);
	temp = ft_strchr(env_str, '=');
	key = ft_substr(env_str, 0, temp - env_str);
	if (temp[1] != '\0')
		value = ft_strdup(temp + 1);
	else
		value = ft_strdup("");
	if (!is_valid_key(key))
	{
		print_error(cmd, env_str, ERROR_INVALID_IDENTIFIER);
		free(key);
		free(value);
		return (1);
	}
	tail = add_env(tail, key, value);
	return (0);
}

static int	print_export_env(t_cmd *cmd, t_state *state)
{
	t_env	*env;

	env = state->env_list;
	while (env)
	{
		ft_putstr_fd("declare -x ", cmd->fd_out);
		ft_putstr_fd(env->key, cmd->fd_out);
		if (env->value)
		{
			ft_putstr_fd("=\"", cmd->fd_out);
			ft_putstr_fd(env->value, cmd->fd_out);
			ft_putendl_fd("\"", cmd->fd_out);
		}
		env = env->next;
	}
	return (0);
}

static void	create_nullvalue_env(t_state *state, char *key)
{
	t_env	*pre_env;
	t_env	*new_env;

	pre_env = find_tail_env(state->env_list);
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	pre_env->next = new_env;
	new_env->key = key;
	new_env->value = NULL;
	new_env->next = NULL;
}

int builtin_execute_export(t_cmd *cmd, t_state *state)
{
	int		i;
	int		argc;
	int		res;

	i = 1;
	res = 0;
	argc = find_argc(cmd->argv);
	if (argc < 2)
		return (print_export_env(cmd, state));
	while (i < argc)
	{
		if (ft_strchr(cmd->argv[i], '='))
		{
			if (!ft_find_env(cmd->argv[i], state->env_list))
				res += for_export_funtion(cmd, cmd->argv[i], state->env_list);
		}
		else
			create_nullvalue_env(state, cmd->argv[i])
		i++;
	}
	if (res > 0)
		return (1);
	else
		return (0);
}
