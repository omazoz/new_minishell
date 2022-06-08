/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:43:04 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:43:08 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

char	**var_without_value(char *content, t_data *data)
{
	char	**var;

	var = ft_malloc(sizeof(char *) * 3, data);
	var[0] = ft_strcdup(content, '=', data);
	var[1] = NULL;
	var[2] = NULL;
	return (var);
}

t_env	*ft_env_lstnew(char *content, t_env *prev, t_data *data)
{
	int		i;
	t_env	*new;

	i = 0;
	new = ft_malloc(sizeof(*new), data);
	new->prev = prev;
	while (content[i] && content[i] != '=')
		i++;
	if (!content[i] || !content[i + 1])
		new->var = var_without_value(content, data);
	else
		new->var = ft_nsplit(content, '=', 2, data);
	new->next = NULL;
	return (new);
}

void	ft_env_addback(t_env *env, t_env *new)
{
	while (env->next)
		env = env->next;
	new->prev = env;
	env->next = new;
}
