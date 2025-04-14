/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:13 by jishin            #+#    #+#             */
/*   Updated: 2025/04/14 17:11:54 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*free_2d_array(char **array)
{
	int	idx;

	idx = 0;
	if (!array)
		return (NULL);
	while (array[idx] != NULL)
		free(array[idx++]);
	free(array);
	return (NULL);
}

void	*free_multiple_array(void *s1, void *s2, void *s3, void *s4)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
	return (NULL);
}
