/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:42:21 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/07 21:17:52 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*copy_tokens(t_token **lst, t_token_type type, int n, t_data *data)
{
	t_token	*new;
	int		i;

	i = 0;
	new = ft_malloc(sizeof(t_token), data);
	new->content = ft_malloc(sizeof(char) * (n + 1), data);
	while (*lst && i < n)
	{
		new->content[i] = (*lst)->content[0];
		i++;
		if ((*lst)->next != NULL)
			*lst = (*lst)->next;
	}
	new->content[i] = '\0';
	new->type = type;
	new->next = NULL;
	return (new);
}

void	manage_whitespaces(t_token **lst, t_token **prev, t_token **head, \
t_data *data)
{
	t_token	*new;

	new = copy_tokens(lst, WHITE_SPACE, 1, data);
	new->prev = *prev;
	token_lst_addback(head, new);
	*prev = new;
	while (*lst && (*lst)->type == WHITE_SPACE)
		*lst = (*lst)->next;
	*lst = (*lst)->prev;
}

static t_token	*concat_tokens(t_token **lst, t_data *data)
{
	t_token	*head;
	t_token	*prev;

	head = NULL;
	prev = NULL;
	while (*lst)
	{
		if ((*lst)->type == QUOTE || (*lst)->type == DQUOTE)
			manage_quotes(lst, &prev, &head, data);
		if ((*lst)->type == LETTER)
			manage_letters(lst, &prev, &head, data);
		if ((*lst)->type == REDIR_IN || (*lst)->type == REDIR_OUT)
			manage_redir(lst, &prev, &head, data);
		if ((*lst)->type == PIPE || (*lst)->type == DOLLAR)
			manage_else(lst, &prev, &head, data);
		if ((*lst)->type == WHITE_SPACE)
			manage_whitespaces(lst, &prev, &head, data);
		if (*lst)
			*lst = (*lst)->next;
	}
	return (head);
}

void	lexer(char *s, t_token **tokens_lst, t_data *data)
{
	t_token	*char_token;
	t_token	*tmp;

	char_token = char_to_token(s, data);
	tmp = char_token;
	*tokens_lst = concat_tokens(&char_token, data);
	free_token_lst(&tmp, data);
/*	while (*tokens_lst)
	{
		printf("%s, %u\n", (*tokens_lst)->content, (*tokens_lst)->type);
		*tokens_lst = (*tokens_lst)->next;

	}*/
}

