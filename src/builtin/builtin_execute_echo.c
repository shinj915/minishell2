/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:07:23 by eunam             #+#    #+#             */
/*   Updated: 2025/05/12 16:46:06 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_isnflag(char *argv)
{
	int	i;
	int	flag;

	flag = 0;
	if (!argv || argv[0] != '-')
		return (0);
	flag++;
	i = flag;
	while (argv[i] != '\0')
	{
		if (argv[i] != 'n')
			return (0);
		i++;
	}
	return (flag);
}

int builtin_execute_echo(t_cmd *cmd, t_state *state)
{
	int	i;
	int	n_flag;

	(void)state;
	i = 1;
	n_flag = 0;
	if (!cmd->argv[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (ft_isnflag(cmd->argv[i]))
	{
		i++;
		n_flag++;
	}
	while(cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], cmd->redir_fd_out);
		if (cmd->argv[i + 1])
			ft_putstr_fd(" ", cmd->redir_fd_out);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", cmd->redir_fd_out);
	return (0);
}
