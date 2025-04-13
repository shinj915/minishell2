/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:28 by jishin            #+#    #+#             */
/*   Updated: 2025/04/13 19:02:00 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(void)
{
	t_state	*state;
	t_token	*token_list;

	state = (t_state *)malloc(sizeof(t_state));
	if (!state)
		return (1);
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
		free_token(token_list);
		state->cmd_line = NULL;
	}
	free(state);
	return (0);
}
