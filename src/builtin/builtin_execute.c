/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:46 by eunam             #+#    #+#             */
/*   Updated: 2025/05/12 17:20:09 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_execute_cd(t_cmd *cmd, t_state *state)
{
	int	argc;

	argc = find_argc(cmd->argv);
	if (argc != 2)
	{
		if (argc == 1)
			print_error(cmd, NULL, ERROR_TOO_FEW_ARGS);
		else
			print_error(cmd, NULL, ERROR_TOO_MANY_ARGS);
		g_exit_status = 1;
		return (1);
	}
	if (chdir(cmd->argv[1]) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		perror(" ");
		return (1);
	}
	ft_update_pwdenv(state); // PWD 환경변수를 지우면 변수를 새로 생성하지 않음... bash에서는 새로 생성됨...
	return (0);
}

int	builtin_execute_pwd(t_cmd *cmd, t_state *state)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd failed");
		ft_putendl_fd("getcwd: cannot access current directory", 2);
	}
	ft_putendl_fd(cwd, cmd->redir_fd_out);
	ft_update_pwdenv(state);
	free(cwd);
	return (0);
}

// utils?
static void	unset_env(t_env **env_list, char *input)
{
	t_env	*pre;
	t_env	*curr;

	pre = NULL;
	curr = *env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, input) == 0)
			delete_env_node(env_list, pre, curr);
		pre = curr;
		curr = curr->next;
	}
}

int builtin_execute_unset(t_cmd *cmd, t_state *state)
{
	int	i;
	int argc;

	i = 1;
	argc = find_argc(cmd->argv);
	while (i < argc)
	{
		unset_env(&state->env_list, cmd->argv[i]);
		i++;
	}
	return (0);
}
