/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:35:34 by jishin            #+#    #+#             */
/*   Updated: 2025/05/09 11:35:00 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_heredoc_delimeter(t_cmd_redir *red, int idx)
{
	char	*itostr;
	char	*delimeter;

	itostr = ft_itoa(idx);
	if (!itostr)
		return (0);
	delimeter = ft_strdup(red->file);
	if (!delimeter)
		return (0);
	free(red->file);
	red->file = ft_strjoin(".heredoctmp", itostr);
	if (!red->file)
		return (0);
	free(itostr);
	return (delimeter);
}

int	is_fd_valid(int fd)
{
	if (fd == -1)
	{
		ft_putendl_fd("minishell: heredoc temp open error", 2);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

static void	print_error_heredoc(char *del)
{
	ft_putstr_fd("minishell: warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(del, 2);
	ft_putendl_fd("')", 2);
}

void	heredoc_prompt(char *del, int fd, char *line, t_state *state)
{
	while (1)
	{
		line = readline("> ");
		if (line != NULL)
		{
			if (ft_strcmp(line, del) == 0)
			{
				free(line);
				break ;
			}
			line = handle_double_quoted_sequence(line, state);
			ft_putendl_fd(line, fd);
		}
		else
		{
			print_error_heredoc(del);
			free(line);
			break ;
		}
		free(line);
	}
	free(del);
}
