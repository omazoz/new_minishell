/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:41:00 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/07 22:54:30 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	update_env(t_env *env, t_data *data)
{
	char	*tmp;
	char	*tmp2;
	t_env	*head;

	tmp = NULL;
	head = env;
	while (env)
	{
		if (env->var && !ft_strcmp(env->var[0], "PWD"))
			if (env->var[1])
				tmp = ft_strdup(env->var[1], data);
		env = env->next;
	}
	env = head;
	tmp2 = getcwd(NULL, 0);
	set_env(data->env, data, "PWD", ft_strdup(tmp2, data));
	free(tmp2);
	if (tmp)
		set_env(data->env, data, "OLDPWD", tmp);
	free_strs(data->env_char, data);
	data->env_char = dup_env(data->env, data);
}

char	*check_path(t_data *data, char *arg)
{
	void		*dir;
	struct stat	st;
	char		*path;


	dir = opendir(arg);
	if (dir)
		return (closedir(dir), arg);
	else
	{
		// closedir(dir);
// puts("abcd");
		path = ft_strjoin(ft_strjoin_char(ft_strdup(ft_getenv(data->env, \
			"PWD"), data), '/', data), arg, data);
		dir = opendir(path);
		if (dir)
			return (closedir(dir), path);
	}
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	if (stat(path, &st) == -1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (S_ISDIR(st.st_mode))
		ft_putstr_fd(": Permission denied\n", 2);
	else
		ft_putstr_fd(": Not a directory\n", 2);
	return (NULL);
}

int	set_path(t_data *data, char *s)
{
	char	*path;

	path = ft_getenv(data->env, s);
	if (!path)
	{
		if (!ft_strcmp("HOME", s))
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		if (!ft_strcmp("OLDPWD", s))
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (!ft_strcmp("OLDPWD", s))
		printf("%s\n", path);
	chdir(path);
	update_env(data->env, data);
	return (0);
}

int	cd_cmd(char **args, t_data *data)
{
	int		chdir_check;
	char	*path;
	char	*tmp;

	if (!args[1] || ((args[1][0] == '~' && ft_strlen(args[1]) == 1)))
		return (set_path(data, "HOME"));
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	path = check_path(data, args[1]);
	if (!path)
		return (1);
	tmp = getcwd(NULL, 0);
	chdir_check = chdir(path);
	if (chdir_check == 0)
	{
		set_env(data->env, data, "OLDPWD", ft_strdup(tmp, data));
		free(tmp);
		update_env(data->env, data);
		return(0);
	}
	if (chdir_check == -1)
	{
		ft_putstr_fd("minishell: cd: no such  file or directory \n", 2);
		free(tmp);
		return(1);
	}

	// if (args[1][0] == '-' && args[1][1] == '\0')
	// 	return (set_path(data, "OLDPWD"));

	return (0);
}
