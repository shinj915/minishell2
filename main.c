/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:28 by jishin            #+#    #+#             */
/*   Updated: 2025/04/03 17:44:40 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

char	*ft_strndup(const char *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (i < n && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_env	*add_env_list(t_env *env_list, char *key, char *value)
{
	t_env	*new_env;
	t_env	*temp;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = key;
	new_env->value = value;
	new_env->next = NULL;
	if (!env_list)
		return (new_env);
	temp = env_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_env;
	return (env_list);
}

t_env	*get_env_list(char **envp)
{
	t_env	*env_list;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		env_list = add_env_list(env_list, key, value);
		i++;
	}
	return (env_list);
}

void	free_state(t_state *state)
{
	t_env	*temp;

	rl_clear_history();
	while (state->env_list)
	{
		temp = state->env_list;
		free(state->env_list->key);
		free(state->env_list->value);
		state->env_list = state->env_list->next;
		free(temp);
	}
	free(state->env_list);
	free(state);
}

int	main(int argc, char **argv, char **envp)
{
	t_state		*state;
	t_cmd_list	*cmd_list;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
	print_banner();
	state = (t_state *)malloc(sizeof(t_state));
	if (!state)
		return (TYPE_FAIL);
	cmd_list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!cmd_list)
	{
		free(state);
		return (TYPE_FAIL);
	}
	state->cmd_list = cmd_list;
	state->env_list = get_env_list(envp);
	free(cmd_list);
	free_state(state);
	return (g_exit_status);
}
