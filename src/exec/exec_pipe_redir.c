/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:04:09 by jishin            #+#    #+#             */
/*   Updated: 2025/05/30 11:31:37 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_fd(t_cmd *cmd, int fd_backup[2])
{
	if (cmd->prev != NULL )
		close(cmd->prev->pipe_fd[0]);
	close(cmd->pipe_fd[1]);
	if (cmd->next == NULL)
		close(cmd->pipe_fd[0]);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	if (fd_backup)
	{
		dup2(fd_backup[0], 0);
		dup2(fd_backup[1], 1);
		close(fd_backup[0]);
		close(fd_backup[1]);
	}
}

void	handle_pipe_and_redirection(t_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		close(cmd->pipe_fd[0]);
		dup2(cmd->pipe_fd[1], 1);
	}
	if (cmd->prev != NULL)
	{
		dup2(cmd->prev->pipe_fd[0], 0);
		close(cmd->prev->pipe_fd[0]);
		close(cmd->prev->pipe_fd[1]);
	}
	if (cmd->fd_in != 0)
		dup2(cmd->fd_in, 0);
	if (cmd->fd_out != 1)
		dup2(cmd->fd_out, 1);
}

int	set_redirection(t_cmd *cmd)
{
	t_cmd_redir	*red;

	red = cmd->redir_list;
	while (red != NULL)
	{
		if (red->redir_type == TYPE_TOKEN_IO_R)
			cmd->fd_out = open(red->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (red->redir_type == TYPE_TOKEN_IO_RR)
			cmd->fd_out = open(red->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (red->redir_type == TYPE_TOKEN_IO_L \
				|| red->redir_type == TYPE_AFTER_HEREDOC)
			cmd->fd_in = open(red->file, O_RDONLY);
		if (cmd->fd_out == -1 || cmd->fd_in == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(red->file, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			g_exit_status = 1;
			return (1);
		}
		red = red->next;
	}
	return (0);
}

int	check_pipe(t_cmd **cmd)
{
	if (pipe((*cmd)->pipe_fd) == -1)
	{
		ft_putendl_fd("minishell: Broken pipe", 2);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}
