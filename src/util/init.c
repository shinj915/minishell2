/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:04:14 by jishin            #+#    #+#             */
/*   Updated: 2025/05/07 15:07:29 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_state	*init_minishell(int *argc, char ***argv, char **envp)
{
	t_state		*state;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
	print_banner();
	state = (t_state *)malloc(sizeof(t_state));
	if (!state)
		return (NULL);
	state->env_list = get_env_list(envp);
	return (state);
}

t_env	*get_env_list(char **envp)
{
	t_env	*env;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
	value = ft_strdup(ft_strchr(envp[i], '=') + 1);
	env = create_new_env(key, value);
	env->next = NULL;
	i++;
	while (envp[i])
	{
		key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		env = add_env(env, key, value);
		i++;
	}
	return (env);
}

void	ft_sigint(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_status = 128 + signo;
	}
}

void	print_banner(void)
{
	printf("/* ********************************************************* */\n");
	printf("/*                                                           */\n");
	printf("/*        ::::   :::: ::::::::: ::::   ::: :::::::::         */\n");
	printf("/*        :+:+: :+:+:    :+:    :+:+:  :+:    :+:            */\n");
	printf("/*        +:+ +:+ +:+    +:+    +:+:+: +:+    +:+            */\n");
	printf("/*        +#+  +  +#+    +#+    +#+ +# +#+    +#+            */\n");
	printf("/*        +#+     +#+    +#+    +#+  +#+#+    +#+            */\n");
	printf("/*        #+#     #+#    #+#    #+#   #+#+    #+#            */\n");
	printf("/*        ###     ### ######### ###    ### #########         */\n");
	printf("/*                                                           */\n");
	printf("/* ********************************************************* */\n");
}
