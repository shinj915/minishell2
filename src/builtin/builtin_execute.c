/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunam <eunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:46 by eunam             #+#    #+#             */
/*   Updated: 2025/05/07 14:07:30 by eunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_execute_cd(t_cmd *cmd, t_state *state)
{
	int	argc;

	(void)state;
	argc = find_argc(cmd->argv);
	if (argc != 2)
	{
		if (argc == 1)
			ft_putendl_fd("cd : too few arguments", cmd->fd_out);
		else
			ft_putendl_fd("cd : too many arguments", cmd->fd_out);
		return (1);
	}
	if (chdir(cmd->argv[1]) != 0)
	{
		ft_putstr_fd("cd: ", cmd->fd_out);
		ft_putstr_fd(cmd->argv[1], cmd->fd_out);
		ft_putendl_fd(": No such file or directory", cmd->fd_out);
		return (1);
	}
	// cd 후 환경변수 업데이트트
	return (0);
}

int	builtin_execute_pwd(t_cmd *cmd, t_state *state)
{
	int		argc;
	char	*cwd;

	(void)state;
	argc = find_argc(cmd->argv);
	if (argc != 1) // 뒷 인자 무시시
		return (1);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd failed");
		ft_putendl_fd("getcwd: cannot access current directory", cmd->fd_out);
	}
	ft_putendl_fd(cwd, cmd->fd_out);
	free(cwd);
	return (0);
}

int builtin_execute_export(t_cmd *cmd, t_state *state)
{
	int		i;
	int		argc;
	t_env	*tail;

	i = 1;
	argc = find_argc(cmd->argv);
	if (argc < 2)
		return (builtin_execute_env(cmd, state));
	tail = find_tail_env(state->env_list);
	while (i < argc)
	{
		if (ft_strchr(cmd->argv[i], '='))
		{
			if (!ft_find_env(cmd->argv[i], state->env_list))
				tail = for_export_funtion(tail, cmd->argv[i]);
		}
		i++;
	}
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
	if (argc < 2)
	{
		ft_putendl_fd("unset: not enough arguments", cmd->fd_out);
		return (1);
    }
	while (i < argc)
	{
		unset_env(&state->env_list, cmd->argv[i]);
		i++;
	}
	return (0);
}

int builtin_execute_env(t_cmd *cmd, t_state *state)
{
	int		argc;
	char	*env_char;
	t_env	*env;
	
	argc = find_argc(cmd->argv);
	if (argc != 1)
		return (1);
	if (!state)
		return (1);
	env = state->env_list;
	while (env)
	{
		env_char = make_envchar(env);
		ft_putendl_fd(env_char, cmd->fd_out);
		free(env_char);
		env = env->next;
	}
	return (0);
}

int	builtin_execute_exit(t_cmd *cmd, t_state *state)
{
	int	argc;

	(void)state;
	argc = find_argc(cmd->argv);
	if (argc == 2)
	{
		printf("argc = 2\n");
		if (!is_exitdigit(cmd->argv[1]))
			exit(ft_atoi(cmd->argv[1]));
		else // 범위를 넘은 숫자 error 처리
		{
			// 오류 메시지 출력?
			exit(225);
		}
	}
	else if (argc > 2)
	{
		ft_putstr_fd("exit: too many arguments", cmd->fd_out);
		return (1);
	}
	else
		exit(0);
	return (0);
}
