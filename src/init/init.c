/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:04:14 by jishin            #+#    #+#             */
/*   Updated: 2025/04/05 20:22:08 by jishin           ###   ########.fr       */
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

void	ft_sigint(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_status = 1;
	}
}
