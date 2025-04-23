/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redirect_util.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:47:05 by jishin            #+#    #+#             */
/*   Updated: 2025/04/23 16:11:50 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	get_arr_size(char const *s, char l, char r)
{
	size_t	result;

	result = 1;
	if (*s != l || *s != r)
		result++;
	while (*s)
	{
		if (*s == l || *s == r)
			result++;
		s++;
	}
	return (result);
}

static char	*make_array(char const **s, char l, char r)
{
	size_t		size;
	char		*result;
	char const	*ptr_s;
	char		*ptr_result;

	size = 1;
	ptr_s = *s;
	if (**s == l || **s == r)
	{
		(*s)++;
		size++;
	}
	while (**s != '\0' && (**s != l && **s != r) && size++)
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

char	**split_with_two_delim(char const *s, char l, char r)
{
	char	**result;
	char	**ptr;
	char	*array;
	size_t	size;

	if (!s)
		return (NULL);
	size = get_arr_size(s, l, r);
	result = (char **)malloc(sizeof(char *) * size);
	if (!result)
		return (NULL);
	ptr = result;
	while (--size)
	{
		array = make_array(&s, l, r);
		if (!array)
		{
			free_split(result, ptr);
			return (NULL);
		}
		*(ptr++) = array;
	}
	*ptr = NULL;
	return (result);
}
