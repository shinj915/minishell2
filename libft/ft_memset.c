/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:30:31 by donjung           #+#    #+#             */
/*   Updated: 2024/03/01 22:09:15 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	void			*ptr;

	ptr = s;
	while (n--)
	{
		*(unsigned char *)s = (unsigned char)c;
		s++;
	}
	return (ptr);
}
