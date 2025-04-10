/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:50:58 by donjung           #+#    #+#             */
/*   Updated: 2024/03/03 20:54:30 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	i;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	s1_len = ft_strlen(s1);
	while (*s1 && ft_strchr(set, *s1))
	{
		s1++;
		s1_len--;
	}
	while (s1_len > 0 && ft_strchr(set, s1[s1_len - 1]))
		s1_len--;
	dest = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!dest)
		return (NULL);
	while (i < s1_len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[s1_len] = '\0';
	return (dest);
}
