/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunam <eunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:42 by eunam             #+#    #+#             */
/*   Updated: 2025/05/06 13:27:42 by eunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_argc(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

t_env	*find_tail_env(t_env *env_list)
{
	t_env	*env;

	if (env_list == NULL)
		return (NULL);
	env = env_list;
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	delete_env_node(t_env **env_list, t_env *pre, t_env *curr)
{
	if (pre == NULL)
		*env_list = curr->next;
	else
		pre->next = curr->next;
	free(curr->key);
	free(curr->value);
	free(curr);
}

char	*make_envchar(t_env *env)
{
	char	*temp;
	char	*envchar;

	if (!env->key || !env->value)
		return (ft_strdup(""));
	envchar = ft_strdup(env->key);
	temp = ft_strjoin(envchar, "=");
	free(envchar);
	envchar = ft_strjoin(temp, env->value);
	free(temp);
	return (envchar);
}

int	is_exitnumber(char *input)
{
	int			i;
	long long	number;

	i = 0;
	while (input[i])
	{
		if (!ft_isdigit(input[i]))
			return (0);
		i++;
	}
	number = ft_atoll(input);
	if (number < INT_MIN || number > INT_MAX)
		return (0);
	return (1);
}