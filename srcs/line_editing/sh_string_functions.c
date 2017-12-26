/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_string_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 15:34:05 by heynard           #+#    #+#             */
/*   Updated: 2017/08/15 15:34:07 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

t_string			*sh_add_char_in_string(t_string *str, char c, size_t size)
{
	t_string		*new;
	t_string		*tmp;

	if ((new = malloc(sizeof(t_string))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: memory allocation failed");
		return (str);
	}
	new->value = c;
	new->selected = 0;
	new->cursor = 0;
	tmp = str;
	while (tmp->cursor == 0)
		tmp = tmp->next;
	new->next = tmp;
	new->prev = tmp->prev;
	tmp->prev = new;
	if (new->prev == NULL)
		return (new);
	new->prev->next = new;
	return (str);
}

t_string			*sh_add_end(t_string *str, char c)
{
	t_string		*new;
	t_string		*tmp;

	if ((new = malloc(sizeof(t_string))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: memory allocation failed");
		return (str);
	}
	new->value = c;
	new->selected = 0;
	new->cursor = 0;
	tmp = str;
	while (tmp->next)
		tmp = tmp->next;
	new->next = NULL;
	new->prev = tmp;
	tmp->next = new;
	return (str);
}

void				sh_print_string(t_line *line)
{
	t_string		*tmp;

	tmp = line->string;
	while (tmp)
	{
		if (tmp->selected)
			ft_dprintf(STDOUT_FILENO, BG_RED);
		if (tmp->cursor)
			ft_dprintf(STDOUT_FILENO, BG_LIGHTGREY);
		write(STDOUT_FILENO, &(tmp->value), 1);
		if (tmp->cursor || tmp->selected)
			ft_dprintf(STDOUT_FILENO, CLEAR);
		tmp = tmp->next;
	}
}

void				sh_remove_cursor(t_line *line)
{
	t_string		*tmp;

	tmp = line->string;
	while (tmp)
	{
		if (tmp->cursor)
			tmp->cursor = 0;
		if (tmp->selected)
			tmp->selected = 0;
		tmp = tmp->next;
	}
}
