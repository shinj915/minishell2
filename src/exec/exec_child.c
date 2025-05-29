/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:59:38 by jishin            #+#    #+#             */
/*   Updated: 2025/05/29 15:49:51 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_executable(char *path)
{
	int		fd;
	char	elf[4];
	char	shebang[2];
	int		n;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	ft_memset(elf, 0, 4);
	ft_memset(shebang, 0, 2);
	n = read(fd, elf, 4);
	if (n == 4 && ft_strncmp(elf, "\177ELF", 4) == 0)
	{
		close(fd);
		return (1);
	}
	lseek(fd, 0, SEEK_SET);
	n = read(fd, shebang, 2);
	if (n == 2 && ft_strncmp(shebang, "#!", 2) == 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static char	*get_exec_path(t_cmd *cmd, t_state *state)
{
	char	*path;
	char	*temp_path;
	char	**path_list;
	int		i;

	path_list = ft_split(ft_getenv(state, "PATH"), ':');
	if (!path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		temp_path = ft_strjoin(path_list[i], "/");
		path = ft_strjoin(temp_path, cmd->exec_file_name);
		free(temp_path);
		if (access(path, F_OK) == 0)
		{
			free_2d_array(path_list);
			return (path);
		}
		free(path);
		i++;
	}
	free_2d_array(path_list);
	return (NULL);
}

static void	check_path_error(t_cmd *cmd, t_state *state, \
								char **envp, char **path)
{
	struct stat	st;

	if (ft_strchr((*path), '/'))
	{
		if (stat((*path), &st) == 0 && S_ISDIR(st.st_mode))
			print_error_external(state, cmd, envp, ERROR_ISDIR);
		if (access((*path), X_OK))
			print_error_external(state, cmd, envp, ERROR_SYSTEM);
	}
	else
		(*path) = get_exec_path(cmd, state);
	if (!(*path))
		print_error_external(state, cmd, envp, ERROR_CMD_NOT_FOUND);
}

static void	execute_child_cmd(t_cmd *cmd, t_state *state)
{
	char	*path;
	int		result;
	char	**envp;

	path = cmd->exec_file_name;
	envp = get_envp(state->env_list);
	if (set_redirection(cmd))
		exit_child_process(state, envp, 1);
	handle_pipe_and_redirection(cmd);
	result = ft_exec_builtin(cmd, state);
	if (result != -1)
		exit_child_process(state, envp, result);
	check_path_error(cmd, state, envp, &path);
	if (!is_executable(path))
		exit_child_process(state, envp, 0);
	execve(path, cmd->argv, envp);
	perror("minishell: execve failed");
	free(path);
	exit_child_process(state, envp, 127);
}

void	execute_child_processes(t_cmd *cmd, t_state *state, pid_t *pid)
{
	int	fd_backup[2];

	fd_backup[0] = dup(STDIN_FILENO);
	fd_backup[1] = dup(STDOUT_FILENO);
	*pid = fork();
	if (*pid < 0)
	{
		perror("fork");
		g_exit_status = 1;
		return ;
	}
	if (*pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		execute_child_cmd(cmd, state);
	}
	else
		close_fd(cmd, fd_backup);
}
