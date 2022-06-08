/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:53:03 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:53:04 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"

int	scan_redir(t_token *lst)
{
	while (lst)
	{
		if (is_redir_sign(lst->type))
		{
			lst = lst->next;
			while (lst && lst->type == WHITE_SPACE)
				lst = lst->next;
			if (lst && is_redir_sign(lst->type))
			{
				ft_putstr_fd("minishell: syntax error near \
unexpected token `", 2);
				ft_putstr_fd(lst->content, 2);
				ft_putstr_fd("'\n", 2);
				return (1);
			}
		}
		lst = lst->next;
	}
	return (0);
}

t_token	*add_redir_type(t_token *lst)
{
	if (lst && lst->next)
	{
		if (lst->type == HERE_DOC && (lst->next->type == WORD \
			|| lst->next->type == DOLLAR))
		{
			lst->type = HERE_DOC_EXPEND;
			lst->next->type = HERE_DOC_EXPEND;
		}
		else
			lst->next->type = lst->type;
	}
	lst = lst->next;
	return (lst);
}

void	add_type(t_token *lst)
{
	while (lst)
	{
		if (lst && is_word(lst->type))
		{
			lst->type = CMD;
			lst = lst->next;
			while (lst && lst->type != PIPE)
			{
				if (is_word(lst->type))
					lst->type = ARG;
				else
					lst = add_redir_type(lst);
				if (lst)
					lst = lst->next;
			}
		}
		if (lst && is_redir_sign(lst->type))
			lst = add_redir_type(lst);
		if (lst)
			lst = lst->next;
	}
}

int	count_nb_cmd(t_token *lst)
{
	int	i;

	i = 1;
	while (lst)
	{
		if (lst->type == PIPE)
			i++;
		lst = lst->next;
	}
	return (i);
}

int	scan_tokens(t_data *data, t_token *lst)
{
	if (scan_redir(lst))
		return (1);
	if (scan_dollar(data, lst))
		return (1);
	data->tokens = del_whitespaces(&lst, data);
	add_type(data->tokens);
	data->nb_cmd = count_nb_cmd(data->tokens);
	return (0);
}
