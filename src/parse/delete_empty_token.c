/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_empty_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:45:37 by jishin            #+#    #+#             */
/*   Updated: 2025/04/14 13:25:44 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_isspace(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (1);
	while (str[i])
	{
		if (!(str[i] == ' ' || (9 <= str[i] && str[i] <= 13)))
			return (0);
		i++;
	}
	return (1);
}

void	delete_empty_token(t_token **token_list)
{
	t_token	*prev;
	t_token	*ptr;
	t_token	*empty;

	ptr = *token_list;
	prev = NULL;
	while (ptr != NULL)
	{
		if (ptr->token_type == TYPE_TOKEN_CHUNK && ft_isspace(ptr->str))
		{
			if (prev)
				prev->next = ptr->next;
			else
				*token_list = ptr->next;
			free_multiple_array(ptr->str, ptr->origin_str, NULL, NULL);
			empty = ptr;
			ptr = ptr->next;
			free(empty);
		}
		else
		{
			prev = ptr;
			ptr = ptr->next;
		}
	}
}
