/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:04:14 by jishin            #+#    #+#             */
/*   Updated: 2025/04/05 15:18:41 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_state	*init_minishell(int *argc, char ***argv, char **envp)
{
	t_state		*state;
	t_cmd_list	*cmd_list;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
	print_banner();
	state = (t_state *)malloc(sizeof(t_state));
	if (!state)
		return (NULL);
	cmd_list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!cmd_list)
	{
		free(state);
		return (NULL);
	}
	state->cmd_list = cmd_list;
	state->env_list = get_env_list(envp);
	return (state);
}

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
