/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:44:39 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:44:42 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

static size_t	mall_size(char const *s, size_t i, char c)
{
	size_t	size;

	size = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		size++;
		i++;
	}
	return (size);
}

static size_t	mine_substr(char const *s, size_t i, char *strs, char c)
{
	size_t	j;

	if (!s)
		return (0);
	j = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		strs[j] = s[i];
		i++;
		j++;
	}
	strs[j] = '\0';
	return (i);
}

char	**ft_nsplit(char *s, char c, int n, t_data *data)
{
	char	**strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strs = ft_malloc(sizeof(char *) * (n + 1), data);
	if (!s)
		return (NULL);
	while (j < n)
	{
		if (j == n - 1)
			strs[j] = ft_malloc(sizeof(char) * (mall_size(s, i, 0) + 1), data);
		else
			strs[j] = ft_malloc(sizeof(char) * (mall_size(s, i, c) + 1), data);
		if (j == n - 1)
			i = mine_substr(s, i, strs[j], 0);
		else
			i = mine_substr(s, i, strs[j], c);
		i++;
		j++;
	}
	strs[n] = 0;
	return (strs);
}
