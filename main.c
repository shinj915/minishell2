/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:28 by jishin            #+#    #+#             */
/*   Updated: 2025/04/04 16:15:33 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char **envp)
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
		return (TYPE_FAIL);
	cmd_list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!cmd_list)
	{
		free(state);
		return (TYPE_FAIL);
	}
	state->cmd_list = cmd_list;
	state->env_list = get_env_list(envp);
	free(cmd_list);
	free_state(state);
	return (g_exit_status);
}
