/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_pwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunam <eunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:26:54 by jishin            #+#    #+#             */
/*   Updated: 2025/05/27 15:24:20 by eunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_execute_pwd(t_cmd *cmd, t_state *state)
{
	char	*cwd;

	(void)state;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("getcwd failed");
	ft_putendl_fd(cwd, cmd->redir_fd_out);
	free(cwd);
	return (0);
}
