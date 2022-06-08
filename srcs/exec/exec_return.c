/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_return.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:41:43 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:41:50 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

extern int	g_exit_status;

void	exec_error(char *msg, t_data *data)
{
	error(NULL, NULL, msg);
	free_all(data);
	g_exit_status = 255;
	exit(g_exit_status);
}

int	exit_fork(t_cmd *lst, t_data *data, int ret)
{
	if (lst->in > 2)
		close(lst->in);
	if (lst->out > 2)
		close(lst->out);
	if (lst->next)
		close(lst->pipe[0]);
	free_all(data);
	return (ret);
}

int	executable_error(t_cmd *lst, t_data *data)
{
	struct stat	st;

	if (lstat(lst->cmd[0], &st) == -1)
	{
		error(lst->cmd[0], NULL, "No such file or directory");
		return (exit_fork(lst, data, 127));
	}
	else if ((st.st_mode & S_IFMT) == S_IFDIR)
		error(lst->cmd[0], NULL, "Is a directory");
	else
		error(lst->cmd[0], NULL, "Permission denied");
	return (exit_fork(lst, data, 126));
}
