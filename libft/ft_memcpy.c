/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:12:40 by donjung           #+#    #+#             */
/*   Updated: 2024/03/01 22:08:41 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void			*ptr;

	ptr = dest;
	if (!dest && !src)
		return (dest);
	while (n--)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		src++;
		dest++;
	}
	return (ptr);
}
