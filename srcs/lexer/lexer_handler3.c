/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 14:54:26 by heynard           #+#    #+#             */
/*   Updated: 2017/12/02 14:54:27 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

t_token			*handle_integer_dless(const char *str, int *i,
										t_token *lst, t_token **current)
{
	(*current)->str[1] = '<';
	(*current)->str[2] = '<';
	(*current)->str[3] = '\0';
	(*current)->type = DLESS;
	lst = save_token((*current), lst);
	(*current) = init_token(ft_strlen(str));
	(*i)++;
	return (lst);
}

t_token			*handle_integer_dgreat(const char *str, int *i,
										t_token *lst, t_token **current)
{
	(*current)->str[1] = '>';
	(*current)->str[2] = '>';
	(*current)->str[3] = '\0';
	(*current)->type = DGREAT;
	lst = save_token((*current), lst);
	(*current) = init_token(ft_strlen(str));
	(*i)++;
	return (lst);
}

t_token			*handle_integer_greatand(const char *str, int *i,
										t_token *lst, t_token **current)
{
	(*current)->str[1] = '>';
	(*current)->str[2] = '&';
	(*current)->str[3] = '\0';
	(*current)->type = GREATAND;
	lst = save_token((*current), lst);
	(*current) = init_token(ft_strlen(str));
	(*i)++;
	return (lst);
}

t_token			*handle_integer(const char *str, int *i,
								t_token *lst, t_token **current)
{
	if ((*current)->pos == 0 && (str[(*i) + 1] == '>' || str[(*i) + 1] == '<'))
	{
		(*current)->str[0] = str[(*i)];
		(*i)++;
		if (str[(*i)] == '<' && str[(*i) + 1] == '<')
			lst = handle_integer_dless(str, i, lst, current);
		else if (str[(*i)] == '>' && str[(*i) + 1] == '>')
			lst = handle_integer_dgreat(str, i, lst, current);
		else if (str[(*i)] == '>' && str[(*i) + 1] == '&')
			lst = handle_integer_greatand(str, i, lst, current);
		else if (str[(*i)] == '>' && str[(*i) + 1] == '|')
			lst = handle_integer_greatpipe(str, i, lst, current);
		else if (str[(*i)] == '<')
			lst = handle_integer_less(str, i, lst, current);
		else if (str[(*i)] == '>')
			lst = handle_integer_great(str, i, lst, current);
		return (lst);
	}
	return (handle_undifined(str, *i, lst, current));
}
