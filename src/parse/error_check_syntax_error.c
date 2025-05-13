/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_syntax_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:58:25 by jishin            #+#    #+#             */
/*   Updated: 2025/05/05 14:23:34 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_invalid_pipe_or_redirect(t_token *ptr, t_token *prev)
{
	if (ptr->token_type == TYPE_TOKEN_PIPE && (prev == NULL || \
		ptr->next == NULL || prev->token_type != TYPE_TOKEN_ARGV || \
		ptr->next->token_type == TYPE_TOKEN_PIPE))
		return (1);
	if (ptr->token_type >= TYPE_TOKEN_IO_L && \
		ptr->token_type <= TYPE_TOKEN_IO_RR && \
		(ptr->next == NULL || ptr->next->token_type != TYPE_TOKEN_ARGV))
		return (1);
	return (0);
}

static int	check_invalid_redirect_argv(t_token *ptr)
{
	if ((ptr->token_type == TYPE_TOKEN_IO_L || \
		ptr->token_type == TYPE_TOKEN_IO_R || \
		ptr->token_type == TYPE_TOKEN_IO_RR) \
		&& (ptr->next != NULL && ptr->next->is_null == TYPE_ARGV_NULL))
		return (1);
	return (0);
}

static void	set_syntax_error(t_token *token_list, t_token *ptr, t_token *prev)
{
	char	*str;

	str = token_list->str;
	if ((ptr->token_type == TYPE_TOKEN_PIPE) \
		&& ((ptr->next != NULL && ptr->next->token_type == TYPE_TOKEN_PIPE) \
		|| prev == NULL))
	{
		token_list->token_type = TYPE_SYNTAX_ERROR;
		token_list->str = ptr->str;
		ptr->str = str;
		return ;
	}
	token_list->token_type = TYPE_SYNTAX_ERROR;
	if (ptr->next == NULL)
	{
		str = ft_strdup("newline");
		if (!str)
			return ;
		free(token_list->str);
		token_list->str = str;
		return ;
	}
	token_list->str = ptr->next->str;
	ptr->next->str = str;
	return ;
}

static void	set_ambiguous_error(t_token *token_list, t_token *ptr)
{
	char	*str;

	token_list->token_type = TYPE_AMBIGUOUS_ERROR;
	str = ft_strdup(ptr->next->origin_str);
	if (str == NULL)
		return ;
	free(token_list->str);
	token_list->str = str;
	return ;
}

void	check_syntax_error(t_token *token_list)
{
	t_token	*ptr;
	t_token	*prev;

	ptr = token_list;
	prev = NULL;
	while (ptr != NULL)
	{
		if (check_invalid_pipe_or_redirect(ptr, prev))
		{
			set_syntax_error(token_list, ptr, prev);
			break ;
		}
		if (check_invalid_redirect_argv(ptr))
		{
			set_ambiguous_error(token_list, ptr);
			break ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}
