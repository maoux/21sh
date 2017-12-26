/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_printchar_inline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 16:47:01 by heynard           #+#    #+#             */
/*   Updated: 2017/08/10 16:47:03 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static int		sh_count_newline(t_line *line)
{
	t_string	*tmp;
	int			count;

	count = 0;
	tmp = line->string;
	while (tmp)
	{
		if (tmp->value == '\n')
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void			sh_print_line(t_shell *shell, t_line *line)
{
	int			tmp;
	int			new_line;

	tmp = line->lsize + shell->prompt_size;
	if ((new_line = sh_count_newline(line)) > 0)
		tputs(tgetstr("rc", NULL), 1, ft_putcharint);
	else
	{
		if (tmp % shell->win_size->ws_col == 0)
			tmp -= 1;
		while (tmp > shell->prompt_size)
		{
			tputs(tgetstr("le", NULL), 1, ft_putcharint);
			tmp--;
		}
	}
	tputs(tgetstr("cd", NULL), 1, ft_putcharint);
	tputs(tgetstr("sc", NULL), 1, ft_putcharint);
	sh_print_string(line);
}

void			sh_delete_char(t_shell *shell, t_line *line)
{
	if (line->string->cursor)
		return ;
	line->string = sh_delete_char_in_string(line->string);
	sh_print_line(shell, line);
	line->lsize -= 1;
}

void			sh_print_char_in_line(t_shell *shell, t_line *line, char c)
{
	line->string = sh_add_char_in_string(line->string, c, line->lsize);
	line->selection = 0;
	sh_print_line(shell, line);
	line->lsize += 1;
}
