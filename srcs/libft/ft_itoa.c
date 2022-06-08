/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:44:24 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:44:30 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

static int	n_len(long nbr)
{
	int	size;

	size = 1;
	if (nbr < 0)
	{
		nbr *= -1;
		size++;
	}
	while (nbr > 9)
	{
		nbr = nbr / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n, t_data *data)
{
	int		size;
	long	nbr;
	char	*dst;

	nbr = n;
	size = n_len(nbr);
	dst = ft_malloc(sizeof(char) * (size + 1), data);
	if (nbr < 0)
	{
		nbr *= -1;
		dst[0] = '-';
	}
	dst[size] = '\0';
	if (nbr == 0)
		dst[0] = '0';
	while (nbr != 0)
	{
		dst[--size] = nbr % 10 + 48;
		nbr /= 10;
	}
	return (dst);
}
