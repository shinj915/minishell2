/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunam <eunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:45:46 by eunam             #+#    #+#             */
/*   Updated: 2025/05/09 12:45:46 by eunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_execute_env(t_cmd *cmd, t_state *state)
{
	int		argc;
	t_env	*env;
	
	argc = find_argc(cmd->argv);
	if (argc > 1)
	{
		print_error(cmd, cmd->argv[1], ERROR_CMD_NOT_FOUND);
		return (127);
	}
	env = state->env_list;
	while (env)
	{
		if (env->value != NULL)
		{
			ft_putstr_fd(env->key, cmd->fd_out);
			ft_putchar_fd('=', cmd->fd_out);
			ft_putendl_fd(env->value, cmd->fd_out);
		}
		env = env->next;
	}
	return (0);
}
