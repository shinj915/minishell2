/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.co.k    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:04:13 by jishin            #+#    #+#             */
/*   Updated: 2025/04/13 19:08:26 by jishin           ###   ########.fr       */
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