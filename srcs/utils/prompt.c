/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:54:01 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:54:02 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

char	*prompt_without_env(t_data *data)
{
	char	*prompt;
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	prompt = ft_strdup(cwd, data);
	prompt = ft_strjoin(prompt, "$ ", data);
	return (prompt);
}

char	*home_prompt(char *prompt, char *cwd, char *home, t_data *data)
{
	if (!ft_strncmp(cwd, home, ft_strlen(home)))
	{
		if (ft_getenv(data->env, "HOME"))
			prompt = ft_strjoin_char(prompt, '~', data);
		cwd = ft_substr(cwd, ft_strlen(home), ft_strlen(cwd), data);
		prompt = ft_strjoin(prompt, cwd, data);
	}
	else
		prompt = ft_strjoin(prompt, cwd, data);
	ft_free(cwd, data);
	return (prompt);
}

char	*get_prompt(t_data *data, char **envp)
{
	char	s[1024];
	char	*cwd;
	char	*prompt;
	char	*user;
	char	*home;

	getcwd(s, sizeof(s));
	cwd = ft_strdup(s, data);
	user = ft_strdup(ft_getenv(data->env, "USER"), data);
	home = ft_strdup(ft_getenv(data->env, "HOME"), data);
	if (!user || !home || !envp[0])
		return (prompt_without_env(data));
	prompt = ft_strdup("\001\033[1;31m\002", data);
	prompt = ft_strjoin(prompt, user, data);
	prompt = ft_strjoin(prompt, "@minishell\001\033[0m\002", data);
	prompt = ft_strjoin_char(prompt, ':', data);
	prompt = ft_strjoin(prompt, "\001\033[1;34m\002", data);
	prompt = home_prompt(prompt, cwd, home, data);
	prompt = ft_strjoin(prompt, "\001\033[0m\002", data);
	prompt = ft_strjoin(prompt, "$ ", data);
	return (prompt);
}
