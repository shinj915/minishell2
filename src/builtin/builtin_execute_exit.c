/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:15:15 by eunam             #+#    #+#             */
/*   Updated: 2025/05/12 15:37:52 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	digitcount(long long int n)
{
	int	cnt;

	cnt = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		cnt++;
	}
	while (n != 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

static int	is_exitdigit(char *input)
{
	int			i;
	int			input_len;
	long long	number;

	i = 0;
	input_len = 0;
	if (input[0] == '+' || input[0] == '-')
		i++;
	while (input[i])
	{
		if (!ft_isdigit(input[i]))
			return (1);
		if (input[i] != '0' || (input[i] == '0' && input_len))
			input_len++;
		i++;
	}
	if (input_len > 19)
		return (1);
	if (input[0] == '-' || input_len == 0)
		input_len++;
	number = ft_atoll(input);
	if (input_len != digitcount(number))
		return (1);
	return (0);
}

int	builtin_execute_exit(t_cmd *cmd, t_state *state)
{
	int	argc;
	int	value;

	(void)state;
	argc = find_argc(cmd->argv);
	write(1, "exit\n", 5);
	if (argc > 1)
	{
		value = is_exitdigit(cmd->argv[1]);
		if (argc == 2 && value == 0)
			return (ft_atoll(cmd->argv[1]));
		else if (value == 1)
		{
			print_error(cmd, cmd->argv[1], ERROR_NUMERIC_REQUIRED);
			return (2);
		}
		else
		{
			print_error(cmd, NULL, ERROR_TOO_MANY_ARGS);
			return (1);
		}
	}
	return (0);
}
