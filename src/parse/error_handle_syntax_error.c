/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_syntax_error.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:51:45 by jishin            #+#    #+#             */
/*   Updated: 2025/04/23 16:11:35 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd_list	*handle_syntax_error(t_token *token_list)
{
	char		*str;
	int			err_code;
	t_cmd_list	*result;
	t_cmd		*cmd;

	if (token_list == NULL)
		str = ft_strdup("");
	else
		str = ft_strdup(token_list->str);
	result = create_cmd_list();
	err_code = token_list->token_type;
	free_token_list(token_list);
	if (str == NULL || result == NULL)
		return (free_multiple_array(str, result, NULL, NULL));
	result->cmd_status = err_code;
	cmd = add_cmd_to_cmd_list(result);
	if (cmd == NULL)
		return (free_multiple_array(str, result, NULL, NULL));
	cmd->exec_file_name = str;
	return (result);
}
