/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:53:09 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:53:11 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_strs(char **strs, t_data *data)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		ft_free(strs[i], data);
		i++;
	}
	ft_free(strs, data);
}
