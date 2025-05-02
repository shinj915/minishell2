/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:13:21 by jishin            #+#    #+#             */
/*   Updated: 2025/05/02 17:22:31 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*create_new_env(char *key, char *value)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = key;
	if (value)
		new_env->value = value;
	new_env->next = NULL;
	return (new_env);
}

t_env	*add_env(t_env *env, char *key, char *value)
{
	t_env	*new_env;
	t_env	*tmp;

	new_env = create_new_env(key, value);
	if (!new_env)
		return (NULL);
	if (!env)
		return (new_env);
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_env;
	return (env);
}

char	*ft_getenv(t_state *state, char *key)
{
	t_env	*env;

	env = state->env_list;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			if (env->value)
				return (env->value);
			else
				return ("");
		}
		env = env->next;
	}
	return (NULL);
}

char	**get_envp(t_env *env_list)
{
	int		i;
	char	**envp;
	t_env	*temp_env;
	char	*temp_str;

	i = 0;
	temp_env = env_list;
	while (temp_env)
	{
		i++;
		temp_env = temp_env->next;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	temp_env = env_list;
	while (temp_env)
	{
		temp_str = ft_strjoin(temp_env->key, "=");
		envp[i] = ft_strjoin(temp_str, temp_env->value);
		temp_env = temp_env->next;
		free(temp_str);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
