/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:41:11 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 22:26:02 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Print the given env `node` data
*/
#include "../../include/minishell.h"

int	env_cmd(t_data	*data)
{
	t_env	*env;

	if (!data->env)
		return (0);
	env = data->env;
	while (env)
	{
		if (env->var[0])
		{
			ft_putstr_fd(env->var[0], 1);
			ft_putstr_fd("=", 1);
			if (env->var[1])
				ft_putstr_fd(env->var[1], 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	return (0);
}
