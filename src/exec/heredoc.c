/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:17:15 by jishin            #+#    #+#             */
/*   Updated: 2025/05/30 12:16:14 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	heredoc_child(t_state *state, char *del, int fd)
{
	char	*line;

	line = NULL;
	heredoc_prompt(del, fd, line, state);
	free_cmd_list(state->cmd_list);
	free_state(state);
}

static int	heredoc_parent(pid_t pid, int *fd, char *del)
{
	int	status;

	signal(SIGINT, heredoc_sigint);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_exit_status = 128 + WTERMSIG(status);
		signal(SIGINT, ft_sigint);
		close(*fd);
		free(del);
		return (1);
	}
	return (0);
}

static int	start_heredoc(t_state *state, char *del, t_cmd_redir *red)
{
	int		fd;
	pid_t	pid;

	fd = open(red->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (is_fd_valid(fd))
		return (1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		g_exit_status = 1;
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		heredoc_child(state, del, fd);
		exit(0);
	}
	else
		if (heredoc_parent(pid, &fd, del))
			return (1);
	close(fd);
	return (0);
}

static int	redirect_heredoc(t_state *state, char *del, t_cmd_redir *red)
{
	if (del == NULL)
		return (1);
	red->redir_type = TYPE_AFTER_HEREDOC;
	if (start_heredoc(state, del, red))
		return (1);
	free(del);
	return (0);
}

int	has_heredoc(t_cmd_list *cmd_list, t_state *state)
{
	t_cmd_redir	*red;
	t_cmd		*cmd;
	char		*del;
	int			i;

	i = 0;
	cmd = cmd_list->head;
	while (cmd != NULL)
	{
		red = cmd->redir_list;
		while (red != NULL)
		{
			if (red->redir_type == TYPE_TOKEN_IO_LL)
			{
				del = get_heredoc_delimeter(red, i++);
				if (redirect_heredoc(state, del, red))
					return (1);
			}
			red = red->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
