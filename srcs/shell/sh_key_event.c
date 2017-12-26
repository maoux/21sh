/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_key_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 18:01:55 by heynard           #+#    #+#             */
/*   Updated: 2017/08/10 18:01:56 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static void			sh_inner_key_event(t_shell *shell, t_line *line, long key)
{
	if (key == KEY_CTRL_I)
		sh_copy(line);
	else if (key == KEY_CTRL_L)
		sh_cut(shell, line, 0);
	else if (key == KEY_CTRL_P)
		sh_paste(shell, line);
	else if (key == KEY_PAD_HOME)
		sh_move_begin(shell, line);
	else if (key == KEY_END)
		sh_move_end(shell, line);
}

void				sh_key_event(t_shell *shell, t_line *line, long key)
{
	if (key >= 32 && key <= 255 && key != 127)
		sh_print_char_in_line(shell, line, key);
	else if (key == KEY_DELETE)
		sh_delete_char(shell, line);
	else if (key == KEY_DELETE)
		sh_delete_char(shell, line);
	else if (key == KEY_LEFT)
		sh_move_left(shell, line);
	else if (key == KEY_RIGHT)
		sh_move_right(shell, line);
	else if (key == KEY_SHIFT_LEFT)
		sh_move_left_word(shell, line);
	else if (key == KEY_SHIFT_RIGHT)
		sh_move_right_word(shell, line);
	else if (key == KEY_UP)
		sh_move_up_histo(shell, line, shell->histo, NULL);
	else if (key == KEY_DOWN)
		sh_move_down_histo(shell, line, shell->histo, NULL);
	else if (key == KEY_CTRL_A)
		sh_select_all(shell, line);
	else if (key == KEY_CTRL_R)
		sh_select_one(shell, line);
	else
		sh_inner_key_event(shell, line, key);
}
