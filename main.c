/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:28 by jishin            #+#    #+#             */
/*   Updated: 2025/04/17 18:10:40 by jishin           ###   ########.fr       */
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
	while (1)
	{
		state->cmd_line = readline("minishell$ ");
		if (state->cmd_line)
		{
			if (state->cmd_line[0] != '\0')
			{
				state->cmd_parse = ft_strdup(state->cmd_line);
				cmd_list = parse(state->cmd_line, state);
			}
			free_cmd_list(cmd_list);
			free(state->cmd_parse);
			add_history(state->cmd_line);
		}
		else
		{
			printf("Ctrl+D exit\n");
			free(state->cmd_line);
			g_exit_status = 130;
			break ;
		}
		free(state->cmd_line);
		state->cmd_line = NULL;
	}
	free_state(state);
	return (0);
}
