/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:34:17 by jishin            #+#    #+#             */
/*   Updated: 2025/05/19 12:44:35 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_error_external(t_cmd *cmd, int err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->exec_file_name, 2);
	if (err == ERROR_ISDIR)
	{
		ft_putendl_fd(": Is a directory", 2);
		exit(126);
	}
	if (err == ERROR_CMD_NOT_FOUND)
	{
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	if (err == ERROR_SYSTEM)
	{
		perror(": ");
		if (errno == ENOENT)
			exit(127);
		if (errno == EACCES)
			exit(126);
	}
}

void	print_error_builtin(t_cmd *cmd, char *env_str, int error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->exec_file_name, 2);
	if (error == ERROR_INVALID_IDENTIFIER)
	{
		ft_putstr_fd(": \'", 2);
		ft_putstr_fd(env_str, 2);
		ft_putendl_fd("\': not a valid identifier", 2);
	}
	if (error == ERROR_TOO_FEW_ARGS)
		ft_putendl_fd(": too few arguments", 2);
	if (error == ERROR_TOO_MANY_ARGS)
		ft_putendl_fd(": too many arguments", 2);
	if (error == ERROR_NO_SUCH_FILE_OF_DIR)
	{
		ft_putstr_fd(": \'", 2);
		ft_putstr_fd(env_str, 2);
		ft_putendl_fd("\': No such file or directory", 2);
	}
	if (error == ERROR_NUMERIC_REQUIRED)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(env_str, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
}

void	print_error_syntax(t_cmd *cmd, int err)
{
	ft_putstr_fd("minishell: ", 2);
	if (err == TYPE_SYNTAX_ERROR)
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(cmd->exec_file_name, 2);
		ft_putstr_fd("\'\n", 2);
		g_exit_status = 2;
	}
	if (err == TYPE_AMBIGUOUS_ERROR)
	{
		ft_putstr_fd(cmd->exec_file_name, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		g_exit_status = 1;
	}
}

void	print_error_parsing(char *cmd_parse)
{
	ft_putendl_fd("minishell: failed command parsing", 2);
	free(cmd_parse);
}
