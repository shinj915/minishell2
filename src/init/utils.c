/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:44:53 by jishin            #+#    #+#             */
/*   Updated: 2025/04/05 14:13:23 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	ft_sigint(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_status = 1;
	}
}
