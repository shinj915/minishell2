/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_cd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:26:14 by jishin            #+#    #+#             */
/*   Updated: 2025/05/12 18:59:17 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int builtin_execute_cd(t_cmd *cmd, t_state *state)
{
	int	argc;

	argc = find_argc(cmd->argv);
	if (argc != 2)
	{
		if (argc == 1)
			print_error_builtin(cmd, NULL, ERROR_TOO_FEW_ARGS);
		else
			print_error_builtin(cmd, NULL, ERROR_TOO_MANY_ARGS);
		g_exit_status = 1;
		return (1);
	}
	if (chdir(cmd->argv[1]) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		perror(" ");
		return (1);
	}
	ft_update_pwdenv(state);
	return (0);
}
