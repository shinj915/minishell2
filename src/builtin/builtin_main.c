/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:56 by eunam             #+#    #+#             */
/*   Updated: 2025/05/12 15:16:25 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin_command(t_cmd *cmd)
{
	if (ft_strcmp(cmd->exec_file_name, "echo") == 0 || 
		ft_strcmp(cmd->exec_file_name, "cd") == 0 || 
		ft_strcmp(cmd->exec_file_name, "pwd") == 0 || 
		ft_strcmp(cmd->exec_file_name, "export") == 0 || 
		ft_strcmp(cmd->exec_file_name, "unset") == 0 || 
		ft_strcmp(cmd->exec_file_name, "env") == 0)
		return (1);
	else
		return (0);
}

int	ft_exec_builtin(t_cmd *cmd, t_state *state)
{
	int	res;

	res = -1;
	if (ft_strcmp(cmd->exec_file_name, "echo") == 0)
		res = builtin_execute_echo(cmd, state);
	else if (ft_strcmp(cmd->exec_file_name, "cd") == 0)
		res = builtin_execute_cd(cmd, state);
	else if (ft_strcmp(cmd->exec_file_name, "pwd") == 0)
		res = builtin_execute_pwd(cmd, state);
	else if (ft_strcmp(cmd->exec_file_name, "export") == 0)
		res = builtin_execute_export(cmd, state);
	else if (ft_strcmp(cmd->exec_file_name, "unset") == 0)
		res = builtin_execute_unset(cmd, state);
	else if (ft_strcmp(cmd->exec_file_name, "env") == 0)
		res = builtin_execute_env(cmd, state);
	else if (ft_strcmp(cmd->exec_file_name, "exit") == 0)
		res = builtin_execute_exit(cmd, state);
	return (res);
}
