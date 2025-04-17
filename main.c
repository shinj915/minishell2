/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:28 by jishin            #+#    #+#             */
/*   Updated: 2025/04/17 19:31:25 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	prompt(t_cmd_list *cmd_list, t_state *state)
{
	while (1)
	{
		state->cmd_line = readline("minishell$ ");
		if (state->cmd_line)
		{
			if (state->cmd_line[0] != '\0')
			{
				state->cmd_parse = ft_strdup(state->cmd_line);
				cmd_list = parse(state->cmd_line, state);
				free_cmd_list(cmd_list);
				free(state->cmd_parse);
				add_history(state->cmd_line);
			}
		}
		else
		{
			printf("Ctrl+D exit\n");
			g_exit_status = 130;
			break ;
		}
		free(state->cmd_line);
		state->cmd_line = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_state		*state;
	t_cmd_list	*cmd_list;

	state = init_minishell(&argc, &argv, envp);
	if (!state)
		return (TYPE_FAIL);
	cmd_list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!cmd_list)
	{
		free(state);
		return (TYPE_FAIL);
	}
	state->cmd_list = cmd_list;
	prompt(cmd_list, state);
	free(cmd_list);
	free_state(state);
	return (0);
}
