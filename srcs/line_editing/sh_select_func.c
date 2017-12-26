/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_select_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 22:06:31 by heynard           #+#    #+#             */
/*   Updated: 2017/08/18 22:06:32 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void				sh_select_all(t_shell *shell, t_line *line)
{
	t_string		*tmp;

	line->selection = line->selection ? 0 : 1;
	tmp = line->string;
	while (tmp->next != NULL)
	{
		tmp->selected = line->selection ? 1 : 0;
		tmp = tmp->next;
	}
	sh_print_line(shell, line);
}

void				sh_select_one(t_shell *shell, t_line *line)
{
	t_string		*tmp;

	tmp = line->string;
	while (tmp->next != NULL)
	{
		if (tmp->cursor)
			break ;
		tmp = tmp->next;
	}
	if (tmp->next != NULL)
	{
		tmp->selected = (tmp->selected == 1) ? 0 : 1;
		tmp->cursor = (tmp->selected == 1) ? 0 : 1;
		tmp->next->cursor = (tmp->selected == 1) ? 1 : 0;
	}
	sh_print_line(shell, line);
	tmp = line->string;
	while (tmp->next != NULL && tmp->selected)
		tmp = tmp->next;
	if (tmp != line->string && tmp->next == NULL)
		line->selection = 1;
	else
		line->selection = 0;
}
