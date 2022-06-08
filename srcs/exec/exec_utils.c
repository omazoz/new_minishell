/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:41:50 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/07 18:41:53 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

extern int	g_exit_status;

int	exec_builtins(t_cmd *lst, t_data *data)
{
	if (!ft_strncmp(lst->cmd[0], "cd", 3))
		return (cd_cmd(lst->cmd, data));
	else if (!ft_strncmp(lst->cmd[0], "pwd", 4))
		return (pwd_cmd());
	else if (!ft_strncmp(lst->cmd[0], "echo", 5))
		return (echo_cmd(lst->cmd));
	else if (!ft_strncmp(lst->cmd[0], "env", 4))
		return (env_cmd(data));
	else if (!ft_strncmp(lst->cmd[0], "export", 7))
		return (export_cmd(lst->cmd, data));
	else if (!ft_strncmp(lst->cmd[0], "unset", 6))
		return (unset_cmd(lst->cmd, data));
	else if (!ft_strncmp(lst->cmd[0], "exit", 6))
		return (exit_cmd(lst->cmd, data));
	return (0);
}

int	check_builtins(t_cmd *lst)
{
	if (!lst->cmd[0])
		return (0);
	if (!ft_strncmp(lst->cmd[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(lst->cmd[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(lst->cmd[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(lst->cmd[0], "env", 4))
		return (1);
	else if (!ft_strncmp(lst->cmd[0], "export", 7))
		return (1);
	else if (!ft_strncmp(lst->cmd[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(lst->cmd[0], "exit", 6))
		return (1);
	return (0);
}

int	is_only_builtin(t_data *data)
{
	if (data->nb_cmd == 1 && check_builtins(data->cmd_lst) \
		&& data->cmd_lst->in == 0 && data->cmd_lst->out == 1)
		return (1);
	return (0);
}

void	link_pipe(t_cmd *lst, t_data *data)
{
	if (lst->next)
	{
		if (pipe(lst->pipe))
			exec_error("Broken pipe", data);
		if (lst->out == 1)
			lst->out = lst->pipe[1];
		else
			close(lst->pipe[1]);
		if (lst->next->in == 0)
			lst->next->in = lst->pipe[0];
		else
			close(lst->pipe[0]);
	}
}

void	print_sig_error_exec(int status)
{
	g_exit_status = WTERMSIG(status) + 128;
	if (g_exit_status == 131)
		ft_putstr_fd("Quit (core dumped)\n", 1);
	if (g_exit_status == 130)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
