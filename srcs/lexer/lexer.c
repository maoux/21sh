/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:45:20 by heynard           #+#    #+#             */
/*   Updated: 2017/09/27 15:45:22 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void				free_lst(t_token *lst)
{
	t_token			*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		ft_strdel(&(tmp->str));
		free(tmp);
	}
}

int					sh_isifs(char c)
{
	if (c == '\n' || c == ' ' || c == '\t' || c == '\r')
		return (1);
	return (0);
}

t_token				*lexerloop(const char *str, int *i,
							t_token *lst, t_token **current)
{
	if ((*current) == NULL)
		(*current) = init_token(ft_strlen(str));
	if (sh_isifs(str[(*i)]))
		lst = handle_ifs(lst, current);
	else if (str[(*i)] == '|')
		lst = handle_pipe(lst, current);
	else if (str[(*i)] == '<')
		lst = handle_lredirect(lst, current);
	else if (str[(*i)] == '>')
		lst = handle_rredirect(lst, current);
	else if (str[(*i)] == ';')
		lst = handle_separator(lst, current);
	else if (str[(*i)] == '&')
		lst = handle_and(lst, current);
	else if (str[(*i)] == '"' || str[(*i)] == '\'')
		lst = handle_quotes(str, i, lst, current);
	else if (ft_isdigit(str[(*i)]))
		lst = handle_integer(str, i, lst, current);
	else
		lst = handle_undifined(str, (*i), lst, current);
	(*i)++;
	return (lst);
}

t_token				*sh_lexer(const char *str, int i, size_t size)
{
	t_token			*lst;
	t_token			*current;

	lst = NULL;
	current = init_token(size);
	while (str[i] != '\0')
		lst = lexerloop(str, &i, lst, &current);
	if (current)
	{
		if (current->pos != 0)
		{
			current->str[current->pos] = '\0';
			lst = save_token(current, lst);
		}
		else
		{
			ft_strdel(&(current->str));
			free(current);
		}
	}
	return (lst);
}
