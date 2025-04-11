/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:20:14 by jishin            #+#    #+#             */
/*   Updated: 2025/04/11 14:22:21 by jishin           ###   ########.fr       */
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
