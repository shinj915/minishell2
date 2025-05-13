/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:45:46 by eunam             #+#    #+#             */
/*   Updated: 2025/05/13 14:21:12 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_execute_env(t_cmd *cmd, t_state *state)
{
	int		argc;
	t_env	*env;

	argc = find_argc(cmd->argv);
	if (argc > 1)
	{
		print_error_builtin(cmd, cmd->argv[1], ERROR_NO_SUCH_FILE_OF_DIR);
		return (127);
	}
	env = state->env_list;
	while (env)
	{
		ft_putstr_fd(env->key, cmd->redir_fd_out);
		ft_putchar_fd('=', cmd->redir_fd_out);
		ft_putendl_fd(env->value, cmd->redir_fd_out);
		env = env->next;
	}
	return (0);
}
