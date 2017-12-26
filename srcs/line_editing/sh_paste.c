/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 14:00:37 by heynard           #+#    #+#             */
/*   Updated: 2017/08/21 14:00:37 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void				sh_paste(t_shell *shell, t_line *line)
{
	t_string		*tmp;
	t_string		*old;
	int				size;

	if (!line->copy)
		return ;
	tmp = line->copy;
	size = 0;
	while (tmp != NULL)
	{
		line->string = sh_add_char_in_string(line->string,
											tmp->value, line->lsize);
		size += 1;
		tmp = tmp->next;
	}
	sh_print_line(shell, line);
	line->lsize += size;
}
