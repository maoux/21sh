/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:48:47 by heynard           #+#    #+#             */
/*   Updated: 2017/09/27 15:48:48 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

t_token			*init_token(size_t size)
{
	t_token		*new;
	char		*str;

	if ((new = malloc(sizeof(t_token))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: memory allocation failed\n");
		return (new);
	}
	if ((str = (char *)malloc(sizeof(char) * size + 1)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: memory allocation failed\n");
		free(new);
		return (NULL);
	}
	ft_bzero((void *)str, size + 1);
	new->pos = 0;
	new->type = DEFAULT;
	new->str = str;
	new->next = NULL;
	return (new);
}

t_token			*save_token(t_token *token, t_token *lst)
{
	t_token		*tmp;

	if (!lst)
		return (token);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
	return (lst);
}

t_token			*handle_ifs(t_token *lst, t_token **current)
{
	if ((*current)->pos == 0)
		return (lst);
	else
	{
		(*current)->str[(*current)->pos] = '\0';
		lst = save_token((*current), lst);
		(*current) = NULL;
		return (lst);
	}
}

t_token			*handle_pipe(t_token *lst, t_token **current)
{
	if ((*current)->pos == 0)
	{
		(*current)->str[(*current)->pos] = '|';
		(*current)->type = PIPE;
		(*current)->pos += 1;
	}
	else if ((*current)->str[0] == '|' || (*current)->str[0] == '>')
	{
		(*current)->str[1] = '|';
		(*current)->str[2] = '\0';
		(*current)->type = ((*current)->str[0] == '|') ? OR_IF : GREATPIPE;
		lst = save_token((*current), lst);
		(*current) = NULL;
	}
	else
	{
		(*current)->str[(*current)->pos] = '\0';
		lst = save_token((*current), lst);
		(*current) = init_token(4);
		(*current)->str[(*current)->pos] = '|';
		(*current)->type = PIPE;
		(*current)->pos += 1;
	}
	return (lst);
}

t_token			*handle_and(t_token *lst, t_token **current)
{
	if ((*current)->pos == 0)
	{
		(*current)->str[(*current)->pos] = '&';
		(*current)->type = AND;
		(*current)->pos = 1;
	}
	else if (((*current)->type == AND || (*current)->type == GREAT) &&
		(*current)->pos < 2)
	{
		(*current)->type = ((*current)->type == AND) ? AND_IF : GREATAND;
		(*current)->str[(*current)->pos] = '&';
		(*current)->pos += 1;
	}
	else
	{
		(*current)->str[(*current)->pos] = '\0';
		lst = save_token((*current), lst);
		(*current) = init_token(4);
		(*current)->str[(*current)->pos] = '&';
		(*current)->type = AND;
		(*current)->pos += 1;
	}
	return (lst);
}
