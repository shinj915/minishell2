/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunam <eunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:42 by eunam             #+#    #+#             */
/*   Updated: 2025/05/27 15:19:54 by eunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_argc(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

t_env	*ft_find_return_env(char *key, t_env *env_list)
{
	t_env	*curr;

	curr = env_list;
	while (curr && ft_strcmp(curr->key, key))
		curr = curr->next;
	if (curr)
		return (curr);
	else
		return (NULL);
}

// void	ft_update_pwdenv(t_state *state)
// {
// 	char	*cwd;
// 	t_env	*pwd;
// 	t_env	*old_pwd;

// 	pwd = ft_find_return_env("PWD", state->env_list);
// 	old_pwd = ft_find_return_env("OLDPWD", state->env_list);
// 	cwd = getcwd(NULL, 0);
// 	if (cwd == NULL)
// 		perror("getcwd failed");
// 	if (old_pwd)
// 	{
// 		if (pwd)
// 		{
// 			free(old_pwd->value);
// 			old_pwd->value = ft_strdup(pwd->value);
// 		}
// 		else
// 			free(cwd);
// 	}
// 	if (pwd)
// 	{
// 		free(pwd->value);
// 		pwd->value = ft_strdup(cwd);
// 	}
// 	free(cwd);
// }

void	ft_update_pwdenv(t_state *state)
{
	char	*cwd;
	t_env	*pwd;
	t_env	*old_pwd;

	pwd = ft_find_return_env("PWD", state->env_list);
	old_pwd = ft_find_return_env("OLDPWD", state->env_list);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("getcwd failed");
	if (old_pwd && pwd)
	{
		free(old_pwd->value);
		old_pwd->value = ft_strdup(pwd->value);
	}
	if (pwd)
	{
		free(pwd->value);
		pwd->value = ft_strdup(cwd);
	}
	else
	{
		pwd = find_tail_env(state->env_list);
		pwd = add_env(pwd, ft_strdup("PWD"), ft_strdup(cwd));
	}
	free(cwd);
}


void	add_nullvalue_env(char *key, t_env *env_list)
{
	char	*dup_key;
	t_env	*new_env;
	t_env	*tail;

	dup_key = ft_strdup(key);
	new_env = create_new_env(dup_key, "NULL");
	tail = find_tail_env(env_list);
	tail->next = new_env;
	new_env->value = NULL;
}

t_env	*ft_find_env(char *env_str, t_env *env_list)
{
	t_env	*env;
	char	*key;
	char	*value;

	if (!env_str)
		return (NULL);
	key = ft_substr(env_str, 0, ft_strchr(env_str, '=') - env_str);
	value = ft_strdup(ft_strchr(env_str, '=') + 1);
	env = ft_find_return_env(key, env_list);
	if (env)
	{
		free(env->value);
		env->value = value;
	}
	else
	{
		free(value);
	}
	free(key);
	return (env);
}
