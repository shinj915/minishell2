/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:28 by jishin            #+#    #+#             */
/*   Updated: 2025/04/05 15:19:27 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_state		*state;
	t_cmd_list	*cmd_list;

	state = init_minishell(&argc, &argv, envp);
	if (!state)
		return (TYPE_FAIL);
	cmd_list = state->cmd_list;
	free(state->cmd_list);
	free_state(state);
	return (g_exit_status);
}
