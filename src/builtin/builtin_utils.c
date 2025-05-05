#include "minishell.h"

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

	envchar = ft_strdup(env->key);
	temp = ft_strjoin(envchar, "=");
	free(envchar);
	envchar = ft_strjoin(temp, env->value);
	free(temp);
	return (envchar);
}
