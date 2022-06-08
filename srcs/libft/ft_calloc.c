/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:42:57 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:43:02 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	*ft_calloc(size_t nmemb, size_t size, t_data *data)
{
	void	*dst;

	dst = ft_malloc(nmemb * size, data);
	ft_bzero(dst, nmemb * size);
	return (dst);
}
