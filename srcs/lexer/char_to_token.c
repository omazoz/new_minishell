/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_to_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:42:11 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/07 21:04:26 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*create_token(char c, t_token_type token_type, t_token *prev, \
t_data *data)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), data);
	new->content = ft_malloc(sizeof(char) * 2, data);
	new->content[0] = c;
	new->content[1] = '\0';
	new->type = token_type;
	new->prev = prev;
	new->next = NULL;
	return (new);
}

static t_token	*token_type(char c, t_token *prev, t_data *data)
{
	if (c == DQUOTE)
		return (create_token(c, DQUOTE, prev, data));
	else if (c == QUOTE)
		return (create_token(c, QUOTE, prev, data));
	else if (c == REDIR_IN)
		return (create_token(c, REDIR_IN, prev, data));
	else if (c == REDIR_OUT)
		return (create_token(c, REDIR_OUT, prev, data));
	else if (c == PIPE)
		return (create_token(c, PIPE, prev, data));
	else if (c == DOLLAR)
		return (create_token(c, DOLLAR, prev, data));
	else if (ft_is_whitespace(c))
		return (create_token(c, WHITE_SPACE, prev, data));
	else
		return (create_token(c, LETTER, prev, data));
	return (NULL);
}

t_token	*char_to_token(char *s, t_data *data)
{
	t_token	*head;
	t_token	*new;
	t_token	*prev;
	int		i;

	i = 0;
	while (s[i] && ft_is_whitespace(s[i]))
		i++;
	prev = NULL;
	new = token_type(s[i], prev, data);
	head = new;
	while (s[++i])
	{
		prev = new;
		new = token_type(s[i], prev, data);
		token_lst_addback(&head, new);
	}
	return (head);
}
