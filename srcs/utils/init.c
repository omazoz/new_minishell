/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:53:52 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:53:55 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

t_env	*mini_env(t_data *data)
{
	t_env	*env;
	char	*tmp;

	data->env_i = 1;
	env = ft_env_lstnew("PWD=", NULL, data);
	tmp = getcwd(NULL, 0);
	set_env(env, data, "PWD", ft_strdup(tmp, data));
	free(tmp);
	env->next = ft_env_lstnew("SHLVL=", NULL, data);
	set_env(env, data, "SHLVL", ft_strdup("1", data));
	env->next->next = ft_env_lstnew("_=", NULL, data);
	set_env(env, data, "_", ft_strdup("./minishell", data));
	return (env);
}

void	update_shlvl(t_env *env, t_data *data)
{
	int	tmp;

	while (env)
	{
		if (!ft_strncmp(env->var[0], "SHLVL", 5))
		{
			if (!env->var[1])
			{
				env->var[1] = ft_strdup("1", data);
				break ;
			}
			tmp = ft_atoi(env->var[1]);
			tmp++;
			ft_free(env->var[1], data);
			env->var[1] = ft_itoa(tmp, data);
		}
		env = env->next;
	}
}
t_env	*init_env(char **envp, t_data *data)
{
	int		i;
	t_env	*env;
	t_env	*tmp;

	i = 1;
	if (!envp[0])
		return (mini_env(data));
	env = ft_env_lstnew(envp[0], NULL, data);
	if (envp[i])
	{
		env->next = ft_env_lstnew(envp[i], env, data);
		i++;
		tmp = env->next;
		while (envp[i])
		{
			tmp->next = ft_env_lstnew(envp[i], tmp, data);
			tmp = tmp->next;
			i++;
			if (!envp[i])
				tmp->next = NULL;
		}
	}
	if (ft_getenv(env, "SHLVL"))
		update_shlvl(env, data);
	return (env);

}
void	init_null(t_data *data)
{
	data->opened = NULL;
	data->tokens = NULL;
	data->cmd_lst = NULL;
	data->fd_error = NULL;
}

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_putstr_fd("minishell: can't malloc data\n", 2);
		exit(EXIT_FAILURE);
	}
	data->garbage = malloc(sizeof(t_garbage));
	if (!data->garbage)
	{
		ft_putstr_fd("minishell: can't malloc data\n", 2);
		free(data);
		exit(EXIT_FAILURE);
	}
	data->garbage->ptr = NULL;
	data->env_i = 0;
	data->env = init_env(envp, data);
	data->env_char = dup_env(data->env, data);
	data->nb_cmd = 0;
	init_null(data);
	return (data);
}
