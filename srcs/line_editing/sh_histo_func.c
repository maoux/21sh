/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histo_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 19:44:50 by heynard           #+#    #+#             */
/*   Updated: 2017/08/17 19:44:51 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static t_string		*add_to_string(t_string *ret, t_string *new)
{
	t_string		*tmp;

	new->selected = 0;
	new->cursor = 0;
	new->next = NULL;
	if (!ret)
	{
		new->prev = NULL;
		return (new);
	}
	tmp = ret;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
	return (ret);
}

static t_string		*add_to_string_last(t_string *ret, t_string *new)
{
	t_string		*tmp;

	new->next = NULL;
	new->selected = 0;
	new->value = ' ';
	new->cursor = 1;
	tmp = ret;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
	return (ret);
}

t_string			*sh_dupline(t_string *str)
{
	t_string		*ret;
	t_string		*new;
	t_string		*tmp;

	ret = NULL;
	tmp = str;
	while (tmp != NULL)
	{
		if ((new = malloc(sizeof(t_string))) == NULL)
		{
			ft_dprintf(STDERR_FILENO, "21sh: memory allocation failed\n");
			return (ret);
		}
		if (tmp->value == '\n')
			new->value = ' ';
		else
			new->value = tmp->value;
		tmp = tmp->next;
		ret = add_to_string(ret, new);
	}
	new->cursor = 1;
	return (ret);
}

t_histo				*sh_insert_histo(t_line *line, t_histo *histo)
{
	t_histo			*new;

	if (line->lsize <= 1)
		return (histo);
	if ((new = malloc(sizeof(t_histo))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: memory allocation failed\n");
		return (histo);
	}
	new->line = sh_dupline(line->string);
	new->lsize = line->lsize;
	new->next = histo;
	new->prev = NULL;
	new->current = 0;
	if (histo)
		histo->prev = new;
	return (new);
}

void				sh_reset_histo(t_histo *histo)
{
	t_histo			*tmp;

	tmp = histo;
	while (tmp)
	{
		tmp->current = 0;
		tmp = tmp->next;
	}
}
