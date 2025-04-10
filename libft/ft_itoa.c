/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donjung <donjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:27:11 by donjung           #+#    #+#             */
/*   Updated: 2024/03/03 21:58:36 by donjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_digits(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		return (11);
	}	
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count + 1);
}

static char	*fill_itoa(int n, int digits, char *array)
{
	int	flag;

	flag = 0;
	array[digits] = '\0';
	digits--;
	if (n < 0)
	{
		flag = 1;
		n = -n;
	}
	while (digits >= 0)
	{
		array[digits] = n % 10 + '0';
		n /= 10;
		digits--;
	}
	if (flag == 1)
		array[0] = '-';
	return (array);
}

char	*ft_itoa(int n)
{
	char	*array;
	int		digits;

	if (n == -2147483648)
	{
		array = (char *)malloc(sizeof(char) * 12);
		ft_memmove(array, "-2147483648", 12);
		return (array);
	}
	digits = check_digits(n);
	array = (char *)malloc(sizeof(char) * (digits + 1));
	if (!array)
		return (NULL);
	fill_itoa(n, digits, array);
	return (array);
}
