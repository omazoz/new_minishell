/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:52:30 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:52:31 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"

extern int	g_exit_status;

void	copy_in_heredoc(int fd, char *s, t_token *lst, t_data *data)
{
	int		i;
	char	*dst;

	i = 0;
	if (!s)
		return ;
	if (lst->type == HERE_DOC_EXPEND)
		dst = find_dollar_value(data, s, i);
	else
	{
		dst = ft_strdup(s, data);
		ft_free(s, data);
	}
	write(fd, dst, ft_strlen(dst));
	ft_free(dst, data);
}

int	check_eof(char *line, char *eof, t_data *data)
{
	char	*dst;

	dst = ft_strdup(line, data);
	if (!ft_strcmp(dst, eof))
	{
		ft_free(dst, data);
		return (1);
	}
	ft_free(dst, data);
	return (0);
}

int	heredoc_loop(char **content, char *eof, t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_exit_status == 130)
			return (1);
		if (!line || !ft_strcmp(line, eof) || check_eof(line, eof, data))
			break ;
		if (!*content)
			*content = ft_strdup(line, data);
		else
			*content = ft_strjoin(*content, line, data);
		*content = ft_strjoin_char(*content, '\n', data);
		free(line);
	}
	return (heredoc_loop_return(*content, line, eof, data));
}

int	manage_heredoc(t_token *lst, char *file_name, char *content, t_data *data)
{
	int		fd;
	pid_t	pid;
	int		dup_stdin;

	sig_reset();
	dup_stdin = dup(0);
	pid = fork();
	if (pid < 0)
		exec_error("fork failed: Resource temporarily unavailable", data);
	if (pid == 0)
	{
		sig_handler_heredoc();
		dup2(dup_stdin, 0);
		fd = ft_open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644, data);
		if (fd < 0)
			return (manage_heredoc_return_error(lst, data));
		if (heredoc_loop(&content, lst->content, data))
			exit_heredoc_fork(data, dup_stdin, file_name);
		copy_in_heredoc(fd, content, lst, data);
		exit_heredoc_fork(data, dup_stdin, NULL);
	}
	waitpid(pid, &g_exit_status, 0);
	g_exit_status = g_exit_status % 255;
	close(dup_stdin);
	return (g_exit_status);
}
