/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:28 by jishin            #+#    #+#             */
/*   Updated: 2025/04/14 11:34:26 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_state	*state;
	t_token	*token_list;

	state = init_minishell(&argc, &argv, envp);
	if (!state)
		return (TYPE_FAIL);
	while (1)
	{
		state->cmd_line = readline("minishell$ ");
		if (state->cmd_line)
		{
			if (state->cmd_line[0] != '\0')
			{
				token_list = parse(state->cmd_line, state);
				print_toklist(token_list);
			}
		}
		else
		{
			printf("Ctrl+D exit\n");
			free(state->cmd_line);
			g_exit_status = 130;
			break ;
		}
		free(state->cmd_line);
		free_token_list(token_list);
		state->cmd_line = NULL;
	}
	free_state(state);
	return (0);
}
