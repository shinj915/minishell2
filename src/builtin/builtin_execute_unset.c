/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:25:18 by jishin            #+#    #+#             */
/*   Updated: 2025/05/12 19:29:02 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	delete_env_node(t_env **env_list, t_env *pre, t_env *curr)
{
	if (pre == NULL)
		*env_list = curr->next;
	else
		pre->next = curr->next;
	free(curr->key);
	free(curr->value);
	free(curr);
}

static void	unset_env(t_env **env_list, char *input)
{
	t_env	*pre;
	t_env	*curr;

	pre = NULL;
	curr = *env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, input) == 0)
		{
			delete_env_node(env_list, pre, curr);
			break ;
		}
		pre = curr;
		curr = curr->next;
	}
}

int	builtin_execute_unset(t_cmd *cmd, t_state *state)
{
	int	i;
	int	argc;

	i = 1;
	argc = find_argc(cmd->argv);
	while (i < argc)
	{
		unset_env(&state->env_list, cmd->argv[i]);
		i++;
	}
	return (0);
}
