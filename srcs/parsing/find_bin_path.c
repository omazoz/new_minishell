/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:52:07 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:52:08 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"

static char	**path_without_env(char *cmd, t_data *data)
{
	char	**path;

	path = ft_malloc(sizeof(char *) * 7, data);
	path[0] = ft_strjoin(ft_strdup("/bin/", data), cmd, data);
	path[1] = ft_strjoin(ft_strdup("/sbin/", data), cmd, data);
	path[2] = ft_strjoin(ft_strdup("/usr/bin/", data), cmd, data);
	path[3] = ft_strjoin(ft_strdup("/usr/sbin/", data), cmd, data);
	path[4] = ft_strjoin(ft_strdup("/usr/local/bin/", data), cmd, data);
	path[5] = ft_strjoin(ft_strdup("/usr/local/sbin/", data), cmd, data);
	path[6] = NULL;
	return (path);
}

static char	**add_cmd_error(char **path, t_data *data)
{
	free_strs(path, data);
	return (NULL);
}

static char	**add_cmd(t_data *data, char *cmd)
{
	int		i;
	char	**path;

	i = 0;
	path = ft_split(ft_getenv(data->env, "PATH"), ':', data);
	if (!path)
		return (add_cmd_error(path, data));
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/", data);
		if (!path[i])
			return (add_cmd_error(path, data));
		path[i] = ft_strjoin(path[i], cmd, data);
		if (!path[i])
			return (add_cmd_error(path, data));
		i++;
	}
	return (path);
}

static int	find_bin_path(t_data *data, t_cmd *lst)
{
	int		i;
	char	**path;

	i = 0;
	path = add_cmd(data, lst->cmd[0]);
	if (!path && data->env_i)
		path = path_without_env(lst->cmd[0], data);
	if (!path)
		return (1);
	while (path[i])
	{
		if (access(path[i], F_OK) == 0)
		{
			lst->bin_path = ft_strdup(path[i], data);
			free_strs(path, data);
			return (0);
		}
		i++;
	}
	free_strs(path, data);
	return (127);
}

int	create_bin_path(t_data *data, t_cmd *lst)
{
	if (access(lst->cmd[0], F_OK) == 0)
		lst->bin_path = ft_strdup(lst->cmd[0], data);
	else
		return (find_bin_path(data, lst));
	return (0);
}
