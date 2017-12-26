/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:48:42 by heynard           #+#    #+#             */
/*   Updated: 2017/09/27 15:48:44 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

t_token			*handle_lredirect(t_token *lst, t_token **current)
{
	if ((*current)->pos == 0)
	{
		(*current)->str[(*current)->pos] = '<';
		(*current)->type = LESS;
		(*current)->pos += 1;
	}
	else if ((*current)->str[0] == '<')
	{
		(*current)->str[1] = '<';
		(*current)->str[2] = '\0';
		(*current)->type = DLESS;
		lst = save_token((*current), lst);
		(*current) = NULL;
	}
	else
	{
		(*current)->str[(*current)->pos] = '\0';
		lst = save_token((*current), lst);
		(*current) = init_token(4);
		(*current)->str[(*current)->pos] = '<';
		(*current)->type = LESS;
		(*current)->pos += 1;
	}
	return (lst);
}

t_token			*handle_rredirect(t_token *lst, t_token **current)
{
	if ((*current)->pos == 0)
	{
		(*current)->str[(*current)->pos] = '>';
		(*current)->type = GREAT;
		(*current)->pos += 1;
	}
	else if ((*current)->str[0] == '>')
	{
		(*current)->str[1] = '>';
		(*current)->str[2] = '\0';
		(*current)->type = DGREAT;
		lst = save_token((*current), lst);
		(*current) = NULL;
	}
	else
	{
		(*current)->str[(*current)->pos] = '\0';
		lst = save_token((*current), lst);
		(*current) = init_token(4);
		(*current)->str[(*current)->pos] = '>';
		(*current)->type = GREAT;
		(*current)->pos += 1;
	}
	return (lst);
}

t_token			*handle_separator(t_token *lst, t_token **current)
{
	if ((*current)->pos == 0)
	{
		(*current)->type = SEMI;
		(*current)->str[0] = ';';
		(*current)->str[1] = '\0';
		lst = save_token((*current), lst);
		(*current) = NULL;
	}
	else
	{
		(*current)->str[(*current)->pos] = '\0';
		lst = save_token((*current), lst);
		(*current) = init_token(4);
		(*current)->type = SEMI;
		(*current)->str[0] = ';';
		(*current)->str[1] = '\0';
		lst = save_token((*current), lst);
		(*current) = NULL;
	}
	return (lst);
}

t_token			*handle_undifined(const char *str, int i, t_token *lst,
									t_token **current)
{
	if ((*current)->type != WORD && (*current)->type != DEFAULT)
	{
		(*current)->str[(*current)->pos] = '\0';
		lst = save_token((*current), lst);
		(*current) = init_token(ft_strlen(str));
	}
	(*current)->type = WORD;
	(*current)->str[(*current)->pos] = str[i];
	(*current)->pos += 1;
	return (lst);
}

t_token			*handle_quotes(const char *str, int *i, t_token *lst,
									t_token **current)
{
	char		q;

	if (str[(*i)] == str[(*i) + 1])
	{
		(*i)++;
		return (lst);
	}
	if ((*current)->type != WORD && (*current)->type != DEFAULT)
	{
		(*current)->str[(*current)->pos] = '\0';
		lst = save_token((*current), lst);
		(*current) = init_token(ft_strlen(str));
	}
	(*current)->type = WORD;
	q = str[(*i)];
	if (q == '`')
		(*current)->type = UNDER_COMMAND;
	(*i)++;
	while (str[(*i)] != q && str[(*i)] != '\0')
	{
		(*current)->str[(*current)->pos] = str[(*i)];
		(*current)->pos++;
		(*i)++;
	}
	return (lst);
}
