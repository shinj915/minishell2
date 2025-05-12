/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunam <eunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:49:26 by eunam             #+#    #+#             */
/*   Updated: 2025/05/08 14:49:26 by eunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_cmd *cmd, char *env_str, int error)
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
	if (error == ERROR_CMD_NOT_FOUND)
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
