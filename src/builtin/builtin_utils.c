/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:42 by eunam             #+#    #+#             */
/*   Updated: 2025/05/13 17:13:20 by jishin           ###   ########.fr       */
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
	if (old_pwd)
	{
		free(old_pwd->value);
		old_pwd->value = ft_strdup(pwd->value);
	}
	if (pwd)
	{
		free(pwd->value);
		pwd->value = ft_strdup(cwd);
	}
	free(cwd);
}
