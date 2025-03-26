/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:58:00 by jishin            #+#    #+#             */
/*   Updated: 2024/09/07 14:58:11 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_num_len(int n)
{
	size_t	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n >= 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*itoa_except(int *p_n, char *result)
{
	if (*p_n == 0)
		result[0] = '0';
	if (*p_n < 0)
	{
		result[0] = '-';
		*p_n = -(*p_n);
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		*p_n;
	size_t	len;
	size_t	i;

	p_n = &n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = get_num_len(n);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		return (0);
	itoa_except(p_n, result);
	i = len - 1;
	while (n > 0)
	{
		result[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	result[len] = '\0';
	return (result);
}
