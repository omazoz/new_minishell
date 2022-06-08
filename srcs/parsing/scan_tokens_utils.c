/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:52:59 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:53:00 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/minishell.h"

int	is_word(t_token_type type)
{
	if (type == WORD || type == DOLLAR
		|| type == IN_DQUOTE || type == IN_QUOTE)
		return (1);
	return (0);
}

int	is_redir_sign(t_token_type token)
{
	if (token == HERE_DOC)
		return (1);
	if (token == DGREATER)
		return (1);
	if (token == REDIR_IN)
		return (1);
	if (token == REDIR_OUT)
		return (1);
	if (token == HERE_DOC_EXPEND)
		return (1);
	return (0);
}
