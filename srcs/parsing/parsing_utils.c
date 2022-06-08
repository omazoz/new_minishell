/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:52:34 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:52:35 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"

t_token	*find_cmd_fd_error(t_token *lst)
{
	ft_putstr_fd("minishell: ", 2);
	perror(lst->content);
	return (lst);
}

t_cmd	*find_cmd_data_error(t_cmd *cmd, t_data *data)
{
	close_all(data);
	free_token_lst(&data->tokens, data);
	ft_free(cmd, data);
	return (NULL);
}

char	*ft_getenv(t_env *env, char *s)
{
	if (!s)
		return (NULL);
	while (env)
	{
		if (env->var && !ft_strcmp(env->var[0], s))
			return (env->var[1]);
		env = env->next;
	}
	return (NULL);
}

static char	*trim_line(char *s, t_data *data)
{
	int				i;
	int				j;
	int				k;
	unsigned int	size;
	char			*ret;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(s) - 1;
	k = 0;
	while (ft_is_whitespace(s[i]))
		i++;
	while (ft_is_whitespace(s[j]) && j > i)
		j--;
	size = j - i;
	ret = ft_malloc(sizeof(char) * (size + 2), data);
	while (i <= j)
		ret[k++] = s[i++];
	ret[k] = '\0';
	return (ret);
}

char	*check_line(char *s, t_data *data)
{
	int		i;
	int		j;
	char	*dst;

	i = ft_strlen(s);
	j = 0;
	dst = NULL;
	while (ft_is_whitespace(s[j]))
		j++;
	if (j == i)
	{
		free(s);
		return (NULL);
	}
	dst = trim_line(s, data);
	free(s);
	return (dst);
}
