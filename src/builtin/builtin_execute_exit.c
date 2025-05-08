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
			return (0);
		i++;
	}
	number = ft_atoll(input);
	if (number < INT_MIN || number > INT_MAX)
		return (0);
	return (1);
}

int	builtin_execute_exit(t_cmd *cmd, t_state *state)
{
	int	argc;

	(void)state;
	argc = find_argc(cmd->argv);
	if (argc == 2)
	{
		printf("argc = 2\n");
		if (!is_exitdigit(cmd->argv[1]))
			exit(ft_atoi(cmd->argv[1]));
		else // 범위를 넘은 숫자 error 처리
		{
			// 오류 메시지 출력?
			exit(225);
		}
	}
	else if (argc > 2)
	{
		ft_putstr_fd("exit: too many arguments", 2);
		return (1);
	}
	else
		exit(0);
	return (0);
}
