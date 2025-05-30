/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute_pwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:26:54 by jishin            #+#    #+#             */
/*   Updated: 2025/05/30 10:50:36 by jishin           ###   ########.fr       */
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
	ft_putendl_fd(cwd, cmd->fd_out);
	free(cwd);
	return (0);
}
