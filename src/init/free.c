/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:14:54 by jishin            #+#    #+#             */
/*   Updated: 2025/04/05 11:35:56 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_state(t_state *state)
{
	t_env	*temp;

	rl_clear_history();
	while (state->env_list)
	{
		temp = state->env_list;
		free(state->env_list->key);
		free(state->env_list->value);
		state->env_list = state->env_list->next;
		free(temp);
	}
	free(state->env_list);
	free(state);
}
