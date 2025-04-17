/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:20:14 by jishin            #+#    #+#             */
/*   Updated: 2025/04/17 18:27:33 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*tokenize(char *cmd, t_state *state)
{
	t_token	*result;

	result = create_token(TYPE_TOKEN_CHUNK, cmd);
	if (!result)
		return (NULL);
	tokenize_quotation(result, state);
	tokenize_env_var(result, state);
	tokenize_space(result);
	delete_empty_token(&result);
	tokenize_pipe(result);
	tokenize_redirect(result);
	tokenize_chunk_to_argv(result);
	delete_space_token(&result);
	check_syntax_error(result);
	return (result);
}

t_cmd_list	*parse(char *cmd, t_state *state)
{
	t_token		*token_list;
	t_cmd_list	*result;

	token_list = tokenize(cmd, state);
	if (!token_list)
		return (NULL);
	if (token_list->token_type == TYPE_SYNTAX_ERROR || \
		token_list->token_type == TYPE_AMBIGOUS_ERROR)
		return (handle_syntax_error(token_list));
	result = tokens_to_cmd_list(token_list);
	free_token_list(token_list);
	return (result);
}
