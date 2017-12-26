/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_move_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 14:50:18 by heynard           #+#    #+#             */
/*   Updated: 2017/08/10 14:50:20 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void			sh_move_left(t_shell *shell, t_line *line)
{
	t_string	*tmp;

	tmp = line->string;
	while (tmp->cursor == 0)
		tmp = tmp->next;
	if (tmp->prev)
	{
		tmp->prev->cursor = 1;
		tmp->cursor = 0;
		if (tmp->prev->value == '\n')
		{
			tmp->prev->cursor = 0;
			tmp->prev->prev->cursor = 1;
		}
		sh_print_line(shell, line);
	}
}

void			sh_move_right(t_shell *shell, t_line *line)
{
	t_string	*tmp;

	tmp = line->string;
	while (tmp->cursor == 0)
		tmp = tmp->next;
	if (tmp->next)
	{
		tmp->next->cursor = 1;
		tmp->cursor = 0;
		if (tmp->next->value == '\n')
		{
			tmp->next->next->cursor = 1;
			tmp->next->cursor = 0;
		}
		sh_print_line(shell, line);
	}
}

void			sh_move_begin(t_shell *shell, t_line *line)
{
	t_string	*tmp;

	if ((tmp = line->string))
	{
		tmp->cursor = 1;
		tmp = tmp->next;
		while (tmp)
		{
			if (tmp->cursor)
				tmp->cursor = 0;
			tmp = tmp->next;
		}
		sh_print_line(shell, line);
	}
}

void			sh_move_end(t_shell *shell, t_line *line)
{
	t_string	*tmp;

	if ((tmp = line->string))
	{
		while (tmp->next)
		{
			if (tmp->cursor)
				tmp->cursor = 0;
			tmp = tmp->next;
		}
		tmp->cursor = 1;
		sh_print_line(shell, line);
	}
}
