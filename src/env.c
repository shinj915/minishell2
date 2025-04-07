/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:13:21 by jishin            #+#    #+#             */
/*   Updated: 2025/04/07 11:34:34 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*add_env(t_env *env_list, char *key, char *value)
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
