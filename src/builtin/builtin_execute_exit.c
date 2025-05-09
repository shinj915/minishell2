/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunam <eunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:15:15 by eunam             #+#    #+#             */
/*   Updated: 2025/05/08 17:15:15 by eunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_exitdigit(char *input)
{
	int			i;
	long long	number;

	i = 0;
	while (input[i])
	{
		if (!ft_isdigit(input[i]))
			return (1);
		i++;
	}
	number = ft_atoll(input);
	if (number < INT_MIN || number > INT_MAX)
		return (1);
	return (0);
}

int	builtin_execute_exit(t_cmd *cmd, t_state *state)
{
	int	argc;
	int	value;

	(void)state;
	argc = find_argc(cmd->argv);
	if (argc > 1)
	{
		value = is_exitdigit(cmd->argv[1]);
		if (argc == 2 && value == 0)
			exit(ft_atoll(cmd->argv[1]));
		else if (value == 1) // 범위를 넘은 숫자 error 처리
		{
			print_error(cmd, cmd->argv[1], ERROR_NUMERIC_REQUIRED);
			// 오류 메시지 출력?numeric argument required
			exit(2);
		}
		else
		{
			print_error(cmd, NULL, ERROR_TOO_MANY_ARGS);
			// ft_putstr_fd("exit: too many arguments", 2);
			return (1);
		}
	}
	else
		exit(0);
	return (0);
}
