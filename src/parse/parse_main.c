/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:20:14 by jishin            #+#    #+#             */
/*   Updated: 2025/04/13 22:49:33 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*tokenize(char *cmd, t_state *state)
{
	t_token	*result;

	(void)state;
	result = create_token(TYPE_TOKEN_CHUNK, cmd);
	if (!result)
		return (NULL);
	tokenize_quotation(result, state);
	tokenize_env_var(result, state);
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
