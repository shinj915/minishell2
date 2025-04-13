/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:04:32 by jishin            #+#    #+#             */
/*   Updated: 2025/04/13 21:10:15 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	get_split_size(char const *s, char c)
{
	size_t	size;

	size = 1;
	if (*s != c)
		size++;
	while (*s)
	{
		if (*s == c)
			size++;
		s++;
	}
	return (size);
}

static char	*split_str(const char **s, char c)
{
	size_t		size;
	char		*result;
	const char	*ptr_s;
	char		*ptr_result;

	size = 1;
	ptr_s = *s;
	if (**s == c)
	{
		(*s)++;
		size++;
	}
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

char	**parse_split(char const *s, char c)
{
	char	**result;
	char	**ptr;
	char	*str;
	size_t	size;

	if (!s)
		return (NULL);
	size = get_split_size(s, c);
	result = (char **)malloc(sizeof(char *) * size);
	if (!result)
		return (NULL);
	ptr = result;
	while (--size)
	{
		str = split_str(&s, c);
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
