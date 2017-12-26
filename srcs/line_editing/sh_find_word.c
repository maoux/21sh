/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_find_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 18:32:37 by heynard           #+#    #+#             */
/*   Updated: 2017/08/17 18:32:39 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static t_string		*sh_find_next_word(t_string *str)
{
	t_string		*tmp;

	tmp = str;
	while (tmp != NULL && tmp->cursor == 0)
		tmp = tmp->next;
	while (tmp != NULL && tmp->value != ' ' && tmp->value != '\t')
		tmp = tmp->next;
	while (tmp != NULL && (tmp->value == ' ' || tmp->value == '\t'))
		tmp = tmp->next;
	return (tmp);
}

static t_string		*sh_find_prev_word(t_string *str)
{
	t_string		*tmp;

	tmp = str;
	while (tmp != NULL && tmp->cursor == 0)
		tmp = tmp->next;
	while (tmp != NULL && tmp->value != ' ' && tmp->value != '\t')
		tmp = tmp->prev;
	while (tmp != NULL && (tmp->value == ' ' || tmp->value == '\t'))
		tmp = tmp->prev;
	if (tmp == NULL)
		return (NULL);
	while (tmp->prev != NULL &&
			tmp->prev->value != ' ' && tmp->prev->value != '\t')
		tmp = tmp->prev;
	return (tmp);
}

void				sh_move_right_word(t_shell *shell, t_line *line)
{
	t_string		*next;

	if ((next = sh_find_next_word(line->string)) != NULL)
	{
		sh_remove_cursor(line);
		next->cursor = 1;
		sh_print_line(shell, line);
	}
}

void				sh_move_left_word(t_shell *shell, t_line *line)
{
	t_string		*next;

	if ((next = sh_find_prev_word(line->string)) != NULL)
	{
		sh_remove_cursor(line);
		next->cursor = 1;
		sh_print_line(shell, line);
	}
}
