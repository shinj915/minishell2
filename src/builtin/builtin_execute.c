#include "minishell.h"

int builtin_execute_echo(t_cmd *cmd, t_state *state)
{
	(void)state;
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (!cmd->argv[1])
		return (1);
	if (ft_strcmp(cmd->argv[1], "-n") == 0)
	{
		i++;
		n_flag = 1;
	}
	while(cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], cmd->fd_out);
		if (cmd->argv[i + 1])
			ft_putstr_fd(" ", cmd->fd_out);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", cmd->fd_out);
	return (0);
}

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
	return (0);
}

int	builtin_execute_pwd(t_cmd *cmd, t_state *state)
{
	int		argc;
    char    *cwd;

	(void)state;
	argc = find_argc(cmd->argv);
	if (argc != 1)
		return (1);
    printf("in builtin_excute_pwd\n");
    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        // error
    }
	ft_putendl_fd(cwd, cmd->fd_out);
    free(cwd);
	return (0);
}

int builtin_execute_export(t_cmd *cmd, t_state *state)
{
	int		i;
	int		argc;
	char	**temp;
	t_env	*tail;

	i = 1;
	argc = find_argc(cmd->argv);
	if (argc < 2)
		return (builtin_execute_env(cmd, state));
	tail = find_tail_env(state->env_list);
	while (i < argc)
	{
		temp = ft_split(cmd->argv[i], '=');
		add_env(tail, temp[0], temp[1]);
		i++;
		free(temp[0]);
		free(temp[1]);
		free(temp);
	}
	return (0);
}

// utils?
void	unset_env(t_env **env_list, char *input)
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
		// if (is_digit(cmd->argv[1])) // 범위도 확인
		// 	exit(ft_atoi(cmd->argv[1]));
		// else
		// {
		// 	// 오류 메시지 출력력
		// 	exit(225);
		// }
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
