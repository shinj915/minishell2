/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:15:15 by eunam             #+#    #+#             */
/*   Updated: 2025/05/26 14:27:42 by jishin           ###   ########.fr       */
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
			return ((unsigned long long)ft_atoll(cmd->argv[1]) % 256);
		else if (value == 1)
		{
			print_error_builtin(cmd, cmd->argv[1], ERROR_NUMERIC_REQUIRED);
			return (2);
		}
		else
		{
			print_error_builtin(cmd, NULL, ERROR_TOO_MANY_ARGS);
			return (-1);
		}
	}
	return (0);
}

int	execute_single_exit(t_cmd *cmd, t_state *state)
{
	int	result;

	result = builtin_execute_exit(cmd, state);
	if (result == -1)
	{
		g_exit_status = 1;
		return (1);
	}
	else
	{
		g_exit_status = result;
		return (EXIT_MINISHELL);
	}
}
