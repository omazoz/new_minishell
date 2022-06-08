/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:52:26 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:52:27 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"

extern int	g_exit_status;

char	*heredoc_filename(t_data *data)
{
	char		*filename;
	struct stat	st;

	filename = ft_strdup("/tmp/", data);
	filename = ft_strjoin_char(filename, '.', data);
	filename = ft_strjoin_char(filename, 8, data);
	if (lstat(filename, &st) == -1)
		return (filename);
	else
		unlink(filename);
	return (filename);
}

int	no_line_return(int i, char *eof, t_data *data)
{
	char	p1;
	char	p2;

	p1 = '(';
	p2 = ')';
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putstr_fd(ft_itoa(i, data), 2);
	ft_putstr_fd(" delimited by end-of-file ", 2);
	write(2, &p1, 1);
	ft_putstr_fd("wanted `", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("'", 2);
	write(2, &p2, 1);
	ft_putstr_fd("\n", 2);
	return (0);
}

int	exit_heredoc_fork(t_data *data, int dup_stdin, char *file_name)
{
	if (file_name)
		unlink(file_name);
	else
		close (0);
	close(dup_stdin);
	close_all(data);
	free_all(data);
	exit (g_exit_status);
}

int	heredoc_loop_return(char *content, char *line, char *eof, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (content && content[i])
	{
		if (content[i] == '\n')
			j++;
		i++;
	}
	if (!line)
		return (no_line_return(j, eof, data));
	free(line);
	return (0);
}

int	manage_heredoc_return_error(t_token *lst, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	perror(lst->content);
	free_all(data);
	return (1);
}
