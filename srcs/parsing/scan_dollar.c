/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:52:56 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:52:57 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"

extern int	g_exit_status;

static char	*exit_dollar_status(int *i, t_data *data)
{
	char	*dst;

	dst = ft_itoa(g_exit_status, data);
	(*i)++;
	return (dst);
}

static char	*copy_dollar(char *s, int *i, t_data *data)
{
	int		j;
	int		len;
	char	*dst;

	j = 0;
	len = 0;
	while (s[*i] && s[*i] == '$')
	{
		len++;
		(*i)++;
	}
	dst = ft_malloc(sizeof(char) * (len + 2), data);
	dst[0] = '$';
	while (j++ < len)
		dst[j] = '$';
	dst[j] = '\0';
	return (dst);
}

static char	*get_env_var(t_data *data, char *s, int *i)
{
	char	*dst;
	char	*tmp;
	char	*env;

	tmp = NULL;
	dst = NULL;
	if (s[*i] && is_dollar_char_valid(s[*i], 1))
		return (get_env_var_return_error(i, data));
	while (check_next_char_dollar(s, i))
	{
		if (s[*i] != '{' && s[*i] != '}')
			tmp = ft_strjoin_char(tmp, s[*i], data);
		if (s[*i] == '}')
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	env = ft_getenv(data->env, tmp);
	if (env)
		dst = ft_strdup(env, data);
	ft_free(tmp, data);
	return (dst);
}

char	*find_dollar_value(t_data *data, char *s, int i)
{
	char	*dst;
	char	*tmp;

	dst = NULL;
	while (s[i])
	{
		if (s[i] && s[i] == '$')
		{
			i++;
			if (s[i] && s[i] == '?')
				tmp = (exit_dollar_status(&i, data));
			else if (!s[i] || (s[i] && is_dollar_char_valid(s[i], 2)))
				tmp = copy_dollar(s, &i, data);
			else
				tmp = get_env_var(data, s, &i);
			dst = join_tmp(dst, tmp, data);
			continue ;
		}
		if (s[i])
			dst = ft_strjoin_char(dst, s[i++], data);
	}
	if (i == 0)
		return (s);
	return (ft_free(s, data), dst);
}

int	scan_dollar(t_data *data, t_token *lst)
{
	int		i;

	while (lst)
	{
		i = 0;
		if ((lst->type == IN_DQUOTE || lst->type == DOLLAR) && !is_heredoc(lst))
			lst->content = find_dollar_value(data, lst->content, i);
		lst = lst->next;
	}
	return (0);
}
