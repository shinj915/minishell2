/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_env_var_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:01:12 by jishin            #+#    #+#             */
/*   Updated: 2025/04/14 09:57:02 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	get_split_size_with_delim(char const *s, char c)
{
	size_t	size;
	int		flag;

	size = 1;
	if (*s != c)
		size++;
	flag = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (!flag)
				size++;
			flag = 1;
		}
		else if (flag)
		{
			size++;
			flag = 0;
		}
		s++;
	}
	return (size);
}

static char	*split_str_with_delim(char const **s, char c)
{
	size_t		size;
	char		*result;
	char const	*ptr_s;
	char		*ptr_result;

	size = 1;
	ptr_s = *s;
	if (**s == c)
		while (**s != '\0' && **s == c && size++)
			(*s)++;
	else
		while (**s != '\0' && **s != c && size++)
			(*s)++;
	result = (char *)malloc(sizeof(char) * size);
	if (!result)
		return (NULL);
	ptr_result = result;
	size--;
	while (size-- && *ptr_s != '\0')
		*(ptr_result++) = *(ptr_s++);
	*ptr_result = '\0';
	return (result);
}

static void	free_split(char **s, char **ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	if (*s == *ptr)
	{
		free(s);
		return ;
	}
	while ((*s) != --(*ptr))
	{
		if ((*ptr) != NULL)
			free(*ptr);
	}
	if (*ptr != NULL)
		free(*ptr);
	free(s);
}

char	**split_with_delim(const char *s, char c)
{
	char	**result;
	char	**ptr;
	char	*str;
	size_t	size;

	if (!s)
		return (NULL);
	size = get_split_size_with_delim(s, c);
	result = (char **)malloc(sizeof(char *) * size);
	if (!result)
		return (NULL);
	ptr = result;
	while (--size)
	{
		str = split_str_with_delim(&s, c);
		if (!str)
		{
			free_split(result, ptr);
			return (NULL);
		}
		*(ptr++) = str;
	}
	*ptr = NULL;
	return (result);
}

void	retokenize_expanded_token(t_token *token)
{
	char	**split;
	int		idx;

	split = split_with_delim(token->str, ' ');
	if (!split)
		return ;
	free(token->str);
	token->str = ft_strdup(split[0]);
	idx = 0;
	while (split[++idx] != NULL)
	{
		if (split[idx][0] == ' ')
			add_token(&token, idx, TYPE_TOKEN_SPACE, split[idx]);
		else
			add_token(&token, idx, token->token_type, split[idx]);
	}
	free_2d_array(split);
}
