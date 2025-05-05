#include "minishell.h"

void	is_builtin_command(t_cmd_list *cmd_list, t_state *state)
{
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	t_cmd	*recent_cmd;

	recent_cmd = cmd_list->head;
	if (ft_strcmp(recent_cmd->argv[0], builtins[0]) == 0)
		builtin_execute_echo(recent_cmd, state);
	else if (ft_strcmp(recent_cmd->argv[0], builtins[1]) == 0)
		builtin_execute_cd(recent_cmd, state);
	else if (ft_strcmp(recent_cmd->argv[0], builtins[2]) == 0)
		builtin_execute_pwd(recent_cmd, state);
	else if (ft_strcmp(recent_cmd->argv[0], builtins[3]) == 0)
		builtin_execute_export(recent_cmd, state);
	else if (ft_strcmp(recent_cmd->argv[0], builtins[4]) == 0)
		builtin_execute_unset(recent_cmd, state);
	else if (ft_strcmp(recent_cmd->argv[0], builtins[5]) == 0)
		builtin_execute_env(recent_cmd, state);
	else if (ft_strcmp(recent_cmd->argv[0], builtins[6]) == 0)
		builtin_execute_exit(recent_cmd, state);
	// add_history(state->cmd_list);
}
