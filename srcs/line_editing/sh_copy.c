/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 13:46:25 by heynard           #+#    #+#             */
/*   Updated: 2017/08/21 13:46:26 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static void			sh_free_string(t_string *str)
{
	t_string		*tmp;

	tmp = str;
	while (tmp)
	{
		tmp = tmp->next;
		free(str);
		str = tmp;
	}
}

static t_string		*sh_add_string(t_string *str, char c)
{
	t_string		*new;
	t_string		*tmp;

	if ((new = malloc(sizeof(t_string))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: memory allocation failed");
		return (str);
	}
	new->value = c;
	new->next = NULL;
	new->prev = NULL;
	if (!str)
		return (new);
	tmp = str;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (str);
}

void				sh_copy(t_line *line)
{
	t_string		*tmp;

	sh_free_string(line->copy);
	line->copy = NULL;
	tmp = line->string;
	while (tmp != NULL)
	{
		if (tmp->selected)
			line->copy = sh_add_string(line->copy, tmp->value);
		tmp = tmp->next;
	}
}

void				sh_cut(t_shell *shell, t_line *line, int i)
{
	t_string		*new;
	t_string		*tmp;

	line->selection = 0;
	sh_free_string(line->copy);
	line->copy = NULL;
	new = NULL;
	tmp = line->string;
	while (tmp != NULL)
	{
		if (tmp->selected)
			line->copy = sh_add_string(line->copy, tmp->value);
		else
		{
			new = sh_add_string(new, tmp->value);
			i++;
		}
		tmp = tmp->next;
	}
	sh_free_string(line->string);
	line->string = new;
	line->string->cursor = 1;
	sh_print_line(shell, line);
	line->lsize = i;
}
