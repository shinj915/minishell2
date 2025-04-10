/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42gyeongsan.kr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:05:13 by donjung           #+#    #+#             */
/*   Updated: 2024/03/20 19:59:05 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char *save, char *new_line)
{
	size_t	save_len;
	size_t	new_line_len;
	char	*result;
	char	*ptr;
	char	*src;

	save_len = 0;
	if (!new_line)
		return (NULL);
	if (save)
		save_len = ft_strlen(save);
	new_line_len = ft_strlen(new_line);
	result = (char *)malloc(sizeof(char) * (save_len + new_line_len + 1));
	if (!result)
		return (NULL);
	ptr = result;
	src = save;
	while (src && *src)
		*ptr++ = *src++;
	src = new_line;
	while (src && *src)
		*ptr++ = *src++;
	*ptr = '\0';
	free(save);
	return (result);
}
