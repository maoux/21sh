/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 13:49:44 by heynard           #+#    #+#             */
/*   Updated: 2017/12/04 13:49:45 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

t_token			*handle_integer_greatpipe(const char *str, int *i,
										t_token *lst, t_token **current)
{
	(*current)->str[1] = '>';
	(*current)->str[2] = '|';
	(*current)->str[3] = '\0';
	(*current)->type = GREATPIPE;
	lst = save_token((*current), lst);
	(*current) = init_token(ft_strlen(str));
	(*i)++;
	return (lst);
}

t_token			*handle_integer_less(const char *str, int *i,
									t_token *lst, t_token **current)
{
	(*current)->str[1] = '<';
	(*current)->str[2] = '\0';
	(*current)->type = LESS;
	lst = save_token((*current), lst);
	(*current) = init_token(ft_strlen(str));
	return (lst);
}

t_token			*handle_integer_great(const char *str, int *i,
								t_token *lst, t_token **current)
{
	(*current)->str[1] = '>';
	(*current)->str[2] = '\0';
	(*current)->type = GREAT;
	lst = save_token((*current), lst);
	(*current) = init_token(ft_strlen(str));
	return (lst);
}
