/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_dollar_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:52:45 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:52:48 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

char	*join_tmp(char *s1, char *s2, t_data *data)
{
	char	*dst;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	dst = ft_strjoin(s1, s2, data);
	if (!dst)
		return (NULL);
	ft_free(s2, data);
	return (dst);
}

int	check_next_char_dollar(char *s, int *i)
{
	if (s[*i] && (ft_isalpha(s[*i]) || ft_isdigit(s[*i]) || s[*i] == '{'
			|| s[*i] == '}' || s[*i] == '_'))
		return (1);
	return (0);
}

char	*get_env_var_return_error(int *i, t_data *data)
{
	char	*dst;

	dst = ft_malloc(sizeof(char) * 1, data);
	dst[0] = '\0';
	(*i)++;
	return (dst);
}

char	*split_whitespaces(char	*content, t_data *data)
{
	int		i;
	char	*dst;
	char	**splited;

	i = 0;
	dst = NULL;
	splited = NULL;
	if (content[0])
	{
		splited = ft_split(content, ' ', data);
		ft_free(content, data);
		dst = ft_strdup(splited[i], data);
		if (splited[i + 1] != NULL)
			dst = ft_strjoin(dst, " ", data);
		i++;
		while (splited[i])
		{
			dst = ft_strjoin(dst, splited[i], data);
			if (splited[i + 1] != NULL)
				dst = ft_strjoin(dst, " ", data);
			i++;
		}
		return (dst);
	}
	return (content);
}
