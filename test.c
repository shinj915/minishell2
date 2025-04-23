/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:17:00 by jishin            #+#    #+#             */
/*   Updated: 2025/04/23 15:14:05 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 파싱 테스트를 위한 소스 파일, 추후 제거 필요 */

#include "minishell.h"

void print_toklist(t_token *tok_list)
{
	t_token *current = tok_list;
	int		i;

	i = 1;
	while (current != NULL)
	{
		printf("Node %d, Token Type: %d, Token String: %s\n", i, current->token_type, current->str);
		current = current->next;
		i++;
	}
}

void print_toklist_ori(t_token *tok_list)
{
	t_token *current = tok_list;
	int		i;

	i = 1;
	while (current != NULL)
	{
		if (current->origin_str)
			printf("Node %d, Token Type: %d, Token String: %s\n", i, current->token_type, current->origin_str);
		current = current->next;
		i++;
	}
}

void print_redir_list(t_cmd_redir *redir_list)
{
	t_cmd_redir *current = redir_list;

	while (current != NULL)
	{
		printf("Redirection File: %s\n", current->file);
		printf("Redirection Type: %d\n", current->redir_type);
		current = current->next;
	}
}

void print_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return;

	printf("Exec File Name: %s\n", cmd->exec_file_name);
	printf("Arguments: ");
	if (cmd->argv)
	{
		for (int i = 0; cmd->argv[i] != NULL; i++)
		{
			printf("%d: %s \n", i, cmd->argv[i]);
		}
	}
	printf("\n");
	printf("File Descriptors: [%d, %d]\n", cmd->pipe_fd[0], cmd->pipe_fd[1]);
	printf("FD In: %d\n", cmd->redir_fd_in);
	printf("FD Out: %d\n", cmd->redir_fd_out);
	print_redir_list(cmd->redir_list);
	printf("\n");
}

void traverse_and_print(t_cmd_list *cmd_list)
{
	t_cmd *current = cmd_list->head;
	int	i;

	i = 0;
	if (cmd_list == NULL)
		return;
	while (current != NULL)
	{
		printf("%i CMD\n", i);
		print_cmd(current);
		i++;
		current = current->next;
	}
}