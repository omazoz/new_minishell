/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:55:33 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/09 17:55:34 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../../include/minishell.h"

void	update_add_env_var(t_env *env, char **var, t_data *data)
{
	char	*value;

	if (env->var[1])
	{
		if (var[1])
		{
			value = ft_strjoin(env->var[1], var[1], data);
			env->var[1] = value;
			ft_free(var[1], data);
		}
		ft_free(var[0], data);
	}
	else
	{
		if (var && var[1])
		{
			ft_free(env->var[0], data);
			ft_free(env->var, data);
			env->var = ft_malloc(sizeof(char *) * 3, data);
			env->var[0] = name_without_plus(var[0], data);
			env->var[1] = var[1];
			env->var[2] = NULL;
		}
		ft_free(var[0], data);
	}
}

void	update_env_var(t_env *env, char **var, t_data *data)
{
	if (env->var[1])
	{
		ft_free(env->var[1], data);
		if (!var[1])
			env->var[1] = NULL;
		else
			env->var[1] = var[1];
		ft_free(var[0], data);
	}
	else
	{
		if (var[1])
		{
			ft_free(env->var[0], data);
			ft_free(env->var, data);
			env->var = ft_malloc(sizeof(char *) * 3, data);
			env->var[0] = var[0];
			env->var[1] = var[1];
			env->var[2] = NULL;
		}
		else
			ft_free(var[0], data);
	}
}

void	add_env_var(char *arg, t_env **env, int n, t_data *data)
{
	char	**tmp;
	char	*var;

	tmp = NULL;
	if (arg[ft_strlen(arg) - 1] != '=')
	{
		tmp = ft_nsplit(arg, '=', 2, data);
		var = name_without_plus(tmp[0], data);
		var = ft_strjoin_char(var, '=', data);
		ft_free(tmp[0], data);
	}
	else
		var = name_without_plus(arg, data);
	if (tmp != NULL && tmp[1])
	{
		var = ft_strjoin(var, tmp[1], data);
		ft_free(tmp[1], data);
		ft_free(tmp, data);
	}
	if (n == 1)
		*env = ft_env_lstnew(var, NULL, data);
	if (n == 2)
		ft_env_addback(*env, ft_env_lstnew(var, NULL, data));
	ft_free(var, data);
}

char	*name_without_plus(char *s, t_data *data)
{
	int		i;
	char	*dest;

	i = 0;
	if (!s)
		return (NULL);
	dest = ft_malloc(sizeof(char) * ft_strlen(s), data);
	while (s[i] && s[i] != '+')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
