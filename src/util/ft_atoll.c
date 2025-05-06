/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunam <eunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:20 by eunam             #+#    #+#             */
/*   Updated: 2025/05/06 13:27:20 by eunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char *str, int index)
{
	while (str[index] == ' ' || (str[index] >= 9 && str[index] <= 13))
		index++;
	return (index);
}

static int	is_negative(char *str, int *sign, int index)
{
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			*sign *= -1;
		index++;
	}
	return (index);
}

static long long	atoi_converter(char *str, int index)
{
	long long	res;

	res = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		res = (res * 10) + str[index] - '0';
		index++;
	}
	return (res);
}

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	result;
	char		*s;

	i = 0;
	sign = 1;
	s = (char *)str;
	i = is_space(s, i);
	i = is_negative(s, &sign, i);
	result = atoi_converter(s, i);
	return (result * sign);
}