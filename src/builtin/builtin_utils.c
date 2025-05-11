/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:42 by eunam             #+#    #+#             */
/*   Updated: 2025/05/11 19:00:34 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int find_argc(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

t_env	*find_tail_env(t_env *env_list)
{
	t_env	*env;

	if (env_list == NULL)
		return (NULL);
	env = env_list;
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	delete_env_node(t_env **env_list, t_env *pre, t_env *curr)
{
	if (pre == NULL)
		*env_list = curr->next;
	else
		pre->next = curr->next;
	free(curr->key);
	free(curr->value);
	free(curr);
}

char	*make_envchar(t_env *env)
{
	char	*temp;
	char	*envchar;

	if (!env->key || !env->value)
		return (ft_strdup(""));
	envchar = ft_strdup(env->key);
	temp = ft_strjoin(envchar, "=");
	free(envchar);
	envchar = ft_strjoin(temp, env->value);
	free(temp);
	return (envchar);
}

t_env	*ft_find_env(char *env_str, t_env *env_list)
{
	t_env	*curr;
	char	*key;
	char	*value;

	if (!env_str)
		return (NULL);
	curr = env_list;
	key = ft_substr(env_str, 0, ft_strchr(env_str, '=') - env_str);
	value = ft_strdup(ft_strchr(env_str, '=') + 1);
	while (curr && ft_strcmp(curr->key, key))
		curr = curr->next;
	if (curr)
		curr->value = value;
	free(key);
	free(value);
	return (curr);
}

void	ft_update_pwdenv(t_state *state)
{
	char	*cwd;
	char	*pwd_env_char;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("getcwd failed");
	pwd_env_char = ft_strjoin("PWD=", cwd);
	ft_find_env(pwd_env_char, state->env_list);
	free(pwd_env_char);
	free(cwd);
}
