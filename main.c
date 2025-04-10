/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:28 by jishin            #+#    #+#             */
/*   Updated: 2025/04/10 20:07:39 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

t_token	*create_token(int token_type, const char *str)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token_type = token_type;
	new_token->is_null = TYPE_INITIAL_STATUS;
	new_token->str = ft_strdup(str);
	if (!new_token->str)
		return (NULL);
	new_token->origin_str = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->str != NULL)
		free(token->str);
	if (token->origin_str != NULL)
		free(token->origin_str);
	free(token);
}

t_token	*tokenize(char *cmd, t_state *state)
{
	t_token	*result;

	(void)state;
	result = create_token(TYPE_TOKEN_CHUNK, cmd);
	if (!result)
		return (NULL);
	return (result);
}

t_token	*parse(char *cmd, t_state *state)
{
	t_token		*tok_list;

	(void)state;
	tok_list = tokenize(cmd, state);
	if (!tok_list)
		return (NULL);
	return (tok_list);
}

int	main(void)
{
	t_state *state;
	t_token *token_list;

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
