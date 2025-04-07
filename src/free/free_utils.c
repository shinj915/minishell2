/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jishin <jishin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:01:17 by jishin            #+#    #+#             */
/*   Updated: 2025/04/07 11:34:24 by jishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (NULL);
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
	return (NULL);
}
