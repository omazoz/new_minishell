/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:41:36 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:41:39 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	free_env_lst(t_env *env, t_data *data)
{
	int		i;

	i = 0;
	while (env->var[i])
	{
		ft_free(env->var[i], data);
		i++;
	}
	ft_free(env->var, data);
	ft_free(env, data);
}

int	check_unset_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg)
	{
		if (!ft_isalpha(arg[0]) && arg[0] != '_')
			return (1);
		while (arg[i])
		{
			if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[i] != '_')
				return (1);
			i++;
		}
	}
	return (0);
}

t_env	*get_free(t_env *env, t_data *data)
{
	t_env	*tmp;

	tmp = env;
	if (!env->prev)
		env->next->prev = NULL;
	else if (!env->next)
	{
		env->prev->next = NULL;
		env = env->prev;
	}
	if (env->prev && env->next)
	{
		env->prev->next = env->next;
		env->next->prev = env->prev;
	}
	if (env->next)
		env = env->next;
	free_env_lst(tmp, data);
	return (env);
}

t_env	*unset_env_var(t_env *env, char *arg, t_data *data)
{
	while (env)
	{
		if (env->var[0] && !ft_strcmp(env->var[0], arg))
		{
			if (!env->prev && !env->next)
				return (NULL);
			env = get_free(env, data);
			break ;
		}
		else if (env->next)
			env = env->next;
		else
			break ;
	}
	while (env->prev)
		env = env->prev;
	return (env);
}

int	unset_cmd(char **args, t_data *data)
{
	int		i;
	int		err;

	i = 1;
	err = 0;
	while (args[i])
	{
		while (args[i] && check_unset_arg(args[i]))
		{
			err = 1;
			error("unset", args[i], "not a valid identifier");
			i++;
		}
		if (!args[i])
			break ;
		if (data->env)
			data->env = unset_env_var(data->env, args[i], data);
		if (!ft_strncmp(args[i], "PATH", 4))
			data->env_i = 0;
		i++;
	}
	free_strs(data->env_char, data);
	data->env_char = dup_env(data->env, data);
	return (err);
}
