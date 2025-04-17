/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:20:14 by jishin            #+#    #+#             */
/*   Updated: 2025/04/17 12:21:30 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*tokenize(char *cmd, t_state *state)
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

t_token	*parse(char *cmd, t_state *state)
{
	t_token		*token_list;

	token_list = tokenize(cmd, state);
	if (!token_list)
		return (NULL);
	return (token_list);
}
