/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:06:30 by donjung           #+#    #+#             */
/*   Updated: 2024/03/22 16:15:35 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_end(char *save, char *new_line, int new_bytes)
{
	size_t	save_len;

	if (!save)
	{
		free(new_line);
		return (NULL);
	}
	save_len = ft_strlen(save);
	if (*save && new_bytes <= 0)
	{
		free(new_line);
		new_line = (char *)malloc(sizeof(char) * (save_len + 1));
		if (!new_line)
			return (NULL);
		ft_memmove(new_line, save, ft_strlen(save));
		new_line[save_len] = '\0';
		ft_bzero(save, ft_strlen(save));
		return (new_line);
	}
	else
	{
		free(new_line);
		return (NULL);
	}
}

static size_t	next(char *str)
{
	char	*ptr;

	if (!str)
		return (0);
	ptr = str;
	while (*ptr && *ptr != '\n')
		ptr++;
	if (*ptr == '\n')
		ptr++;
	return (ptr - str);
}

static char	*sub(char *str, int start, int len, int flag)
{
	char	*substr;

	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_memmove(substr, str + start, len + 1);
	substr[len] = '\0';
	if (!*substr)
	{
		free(str);
		free(substr);
		return (NULL);
	}
	if (flag == 1)
		free(str);
	return (substr);
}

char	*gnl_handle(char *new_line, int fd)
{
	static char	*s[OPEN_MAX];
	int			new_bytes;

	new_line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new_line)
		return (NULL);
	while (!ft_strchr(s[fd], '\n'))
	{
		new_bytes = read(fd, new_line, BUFFER_SIZE);
		if (new_bytes <= 0)
		{
			new_line = check_end(s[fd], new_line, new_bytes);
			free(s[fd]);
			s[fd] = NULL;
			return (new_line);
		}
		new_line[new_bytes] = '\0';
		s[fd] = gnl_strjoin(s[fd], new_line);
	}
	free(new_line);
	new_line = sub(s[fd], 0, next(s[fd]), 0);
	s[fd] = sub(s[fd], next(s[fd]), ft_strlen(s[fd]) - next(s[fd]), 1);
	return (new_line);
}

char	*get_next_line(int fd)
{
	char		*new_line;

	new_line = NULL;
	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	return (gnl_handle(new_line, fd));
}
