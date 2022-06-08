/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:53:42 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:53:45 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	ft_garb_addback(t_data *data, t_garbage *new)
{
	while (data->garbage->next)
		data->garbage = data->garbage->next;
	new->prev = data->garbage;
	data->garbage->next = new;
	while (data->garbage->prev)
		data->garbage = data->garbage->prev;
}

t_garbage	*ft_garb_lstnew(void *ptr, t_data *data)
{
	t_garbage	*new;

	new = malloc(sizeof(*new));
	if (!new)
	{
		free_all(data);
		printf("minishell: malloc error: terminal killed\n");
		exit(1);
	}
	new->prev = NULL;
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}

void	*ft_malloc(size_t size, t_data *data)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		free_all(data);
		printf("minishell: malloc error: terminal killed\n");
		exit(1);
	}
	if (data->garbage && data->garbage->ptr)
		ft_garb_addback(data, ft_garb_lstnew(ptr, data));
	else if (data->garbage)
	{
		data->garbage->prev = NULL;
		data->garbage->ptr = ptr;
		data->garbage->next = NULL;
	}
	return (ptr);
}
