/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:53:14 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 22:19:35 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../include/minishell.h"

void	remove_garbage(void *ptr, t_data *data)
{
	t_garbage	*tmp;

	while (data->garbage && data->garbage->ptr != ptr)
		data->garbage = data->garbage->next;
	tmp = data->garbage;
	if (data->garbage && !data->garbage->prev && !data->garbage->next)
		return (free(tmp));
	if (data->garbage && !data->garbage->prev)
		data->garbage->next->prev = NULL;
	else if (data->garbage && !data->garbage->next)
	{
		data->garbage->prev->next = NULL;
		data->garbage = data->garbage->prev;
	}
	if (data->garbage && data->garbage->prev && data->garbage->next)
	{
		data->garbage->prev->next = data->garbage->next;
		data->garbage->next->prev = data->garbage->prev;
	}
	if (data->garbage && data->garbage->next)
		data->garbage = data->garbage->next;
	free(tmp);
	while (data->garbage && data->garbage->prev)
		data->garbage = data->garbage->prev;
}

void	ft_free(void *ptr, t_data *data)
{
	free(ptr);
	remove_garbage(ptr, data);
}

void	free_lst(t_data *data)
{
	free_token_lst(&data->tokens, data);
	free_cmd_lst(&data->cmd_lst, data);
}

void	free_all(t_data *data)
{
	ft_free_garbage(data->garbage);
	free(data);
	// rl_clear_history();
}
