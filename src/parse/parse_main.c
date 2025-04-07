/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:16:29 by jishin            #+#    #+#             */
/*   Updated: 2025/04/07 11:34:32 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd_list	*ft_parse(char *cmd, t_state *state)
{
	t_token		*token_list;
	t_cmd_list	*result;

	token_list = ft_tokenize(cmd, state);
	if (!token_list)
		return (NULL);
	if (token_list->token_type == TYPE_SYNTAX_ERROR \
		|| token_list->token_type == TYPE_AMBIGOUS_ERROR)
		return (handle_syntax_error(token_list));
	result = interpret_tokens(token_list);
	free_token_list(token_list);
	return (result);
}
