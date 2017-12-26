/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 15:27:54 by heynard           #+#    #+#             */
/*   Updated: 2017/08/15 15:27:55 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

t_string			*first_space(void)
{
	t_string		*new;

	if ((new = malloc(sizeof(t_string))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: memory allocation failed");
		return (NULL);
	}
	new->prev = NULL;
	new->next = NULL;
	new->value = ' ';
	new->selected = 0;
	new->cursor = 1;
	return (new);
}

void				sh_init_line(t_shell *shell, t_line *line)
{
	if (line)
	{
		line->string = first_space();
		line->lsize = 1;
		line->selection = 0;
		line->copy = NULL;
	}
}

void				sh_free_line(t_line *line)
{
	t_string		*tmp;

	if (line)
	{
		while (line->string)
		{
			tmp = line->string;
			line->string = line->string->next;
			free(tmp);
		}
		while (line->copy)
		{
			tmp = line->copy;
			line->copy = line->copy->next;
			free(tmp);
		}
		line->lsize = 0;
	}
}
