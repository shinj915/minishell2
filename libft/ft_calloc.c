/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:18:04 by donjung           #+#    #+#             */
/*   Updated: 2024/03/03 20:07:00 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tmp;
	size_t			total;
	void			*arr;

	total = nmemb * size;
	if (nmemb == 0 || size == 0)
	{
		arr = malloc(1);
		if (!arr)
			return (NULL);
		*((unsigned char *)arr) = 0;
		return (arr);
	}
	arr = malloc(total);
	if (!arr)
		return (NULL);
	tmp = (unsigned char *)arr;
	while (total--)
	{
		*tmp = 0;
		tmp++;
	}
	return (arr);
}
