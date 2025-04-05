/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:13:21 by jishin            #+#    #+#             */
/*   Updated: 2025/04/05 11:47:30 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*add_env_list(t_env *env_list, char *key, char *value)
{
	t_env	*new_env;
	t_env	*temp;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = key;
	new_env->value = value;
	new_env->next = NULL;
	if (!env_list)
		return (new_env);
	temp = env_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_env;
	return (env_list);
}

t_env	*get_env_list(char **envp)
{
	t_env	*env_list;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		env_list = add_env_list(env_list, key, value);
		i++;
	}
	return (env_list);
}
