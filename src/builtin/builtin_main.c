/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunam <eunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:56 by eunam             #+#    #+#             */
/*   Updated: 2025/05/06 21:34:22 by eunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin_command(t_cmd *cmd, t_state *state)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		builtin_execute_echo(cmd, state);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		builtin_execute_cd(cmd, state);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		builtin_execute_pwd(cmd, state);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		builtin_execute_export(cmd, state);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		builtin_execute_unset(cmd, state);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		builtin_execute_env(cmd, state);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		builtin_execute_exit(cmd, state);
}
