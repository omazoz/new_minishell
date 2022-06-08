/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:52:41 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:52:42 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"

extern int	g_exit_status;

static t_token	*manage_out_redir(t_cmd *new, t_token *lst, t_data *data)
{
	if (lst->type == REDIR_OUT || lst->type == DGREATER)
	{
		if (new->out > 2)
			close(new->out);
		if (lst->type == REDIR_OUT)
			new->out = ft_open(lst->content, O_CREAT | O_WRONLY | O_TRUNC, \
						0644, data);
		else if (lst->type == DGREATER)
			new->out = ft_open(lst->content, O_CREAT | O_WRONLY | O_APPEND, \
						0644, data);
		if (new->out < 0)
			return (new_fd_error(lst, data));
	}
	return (lst);
}

static t_token	*find_cmd_fd(t_cmd *new, t_token *lst, t_data *data)
{
	char	*heredoc_name;

	lst = lst->next;
	if ((lst->type == REDIR_IN || lst->type == HERE_DOC \
		|| lst->type == HERE_DOC_EXPEND))
	{
		if (new->in > 2)
			close(new->in);
		if (lst->type == REDIR_IN)
			new->in = ft_open(lst->content, O_RDONLY, 0, data);
		else if (lst->type == HERE_DOC || lst->type == HERE_DOC_EXPEND)
		{
			g_exit_status = 0;
			heredoc_name = heredoc_filename(data);
			if (manage_heredoc(lst, heredoc_name, NULL, data))
				return (NULL);
			new->in = ft_open(heredoc_name, O_RDONLY, 0, data);
			unlink(heredoc_name);
			ft_free(heredoc_name, data);
		}
		if (new->in < 0)
			return (new_fd_error(lst, data));
	}
	return (manage_out_redir(new, lst, data));
}

static t_cmd	*find_cmd_data(t_token **lst, t_cmd *new, t_data *data, int i)
{
	new->cmd = ft_malloc(sizeof(char *) * (find_cmd_length(*lst) + 1), data);
	while (*lst && (*lst)->type != PIPE)
	{
		if ((*lst)->type == CMD)
		{
			new->cmd_name = ft_strdup((*lst)->content, data);
			new->cmd[i++] = ft_strdup((*lst)->content, data);
		}
		if (*lst && (*lst)->type == ARG)
			new->cmd[i++] = ft_strdup((*lst)->content, data);
		if (*lst && is_redir_sign((*lst)->type))
		{
			if (new->in != -1 && new->out != -1)
				*lst = find_cmd_fd(new, *lst, data);
			if (!(*lst))
				return (find_cmd_data_error(new, data));
		}
		if (*lst)
			*lst = (*lst)->next;
	}
	new->cmd[i] = NULL;
	return (new);
}

static t_cmd	*create_cmd_lst(t_token *lst, t_data *data)
{
	t_cmd	*head;
	t_cmd	*new;
	t_cmd	*prev;

	head = NULL;
	new = NULL;
	prev = NULL;
	while (lst)
	{
		new = ft_malloc(sizeof(t_cmd), data);
		fill_cmd_data(new);
		new = find_cmd_data(&lst, new, data, 0);
		if (!new)
		{
			if (head)
				free_cmd_lst(&head, data);
			return (NULL);
		}
		cmd_lst_addback(&head, new, prev);
		prev = new;
		if (lst)
			lst = lst->next;
	}
	return (head);
}

int	parsing(char *line, t_data *data)
{
	t_token	*tokens_lst;

	tokens_lst = NULL;
	if (first_check(line))
		return (free(line), 1);
	line = check_line(line, data);
	if (!line)
		return (1);
	lexer(line, &tokens_lst, data);
	if (scan_tokens(data, tokens_lst))
		return (ft_free(line, data), 1);
	free_token_lst(&tokens_lst, data);
	data->cmd_lst = create_cmd_lst(data->tokens, data);
	print_fd_error(data);
	if (!data->cmd_lst)
		return (1);
	else if (data->nb_cmd != 1)
		set_env(data->env, data, "_", NULL);
	else
		set_env(data->env, data, "_", ft_strdup(data->cmd_lst->cmd[0], data));
	return (0);
}
