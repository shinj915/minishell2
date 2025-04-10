/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:54:20 by donjung           #+#    #+#             */
/*   Updated: 2024/03/03 20:53:49 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total;
	char	*dest;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * total + 1);
	if (!dest)
		return (NULL);
	ptr = dest;
	while (*s1)
	{
		*dest = *s1;
		dest++;
		s1++;
	}
	while (*s2)
	{
		*dest = *s2;
		dest++;
		s2++;
	}
	*dest = '\0';
	return (ptr);
}
