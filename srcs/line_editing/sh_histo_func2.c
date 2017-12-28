/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_histo_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 20:05:08 by heynard           #+#    #+#             */
/*   Updated: 2017/08/17 20:05:10 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static void		sh_free_string(t_string *str)
{
	t_string	*tmp;

	tmp = str;
	while (tmp)
	{
		tmp = tmp->next;
		free(str);
		str = tmp;
	}
}

int				sh_update_lsize(t_histo *histo, t_histo *tmp, int cases)
{
	if (cases == 1)
	{
		if (tmp == NULL)
			return (histo->lsize);
		else if (tmp->next != NULL)
			return (tmp->next->lsize);
	}
	else if (cases == 2)
	{
		if (tmp->prev == NULL)
			return (1);
		else
			return (tmp->prev->lsize);
	}
	return (0);
}

t_histo			*sh_find_current(t_histo *tmp)
{
	while (tmp != NULL)
	{
		if (tmp->current)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void			sh_move_up_histo(t_shell *shell, t_line *line, t_histo *histo,
									t_histo *tmp)
{
	if (!histo)
		return ;
	tmp = histo;
	tmp = sh_find_current(tmp);
	if (tmp == NULL)
	{
		histo->current = 1;
		sh_free_string(line->string);
		line->string = sh_dupline(histo->line);
	}
	else if (tmp->next != NULL)
	{
		tmp->next->current = 1;
		tmp->current = 0;
		sh_free_string(line->string);
		line->string = sh_dupline(tmp->next->line);
	}
	else
		return ;
	sh_print_line(shell, line);
	line->lsize = sh_update_lsize(histo, tmp, 1);
}

void			sh_move_down_histo(t_shell *shell, t_line *line, t_histo *histo,
									t_histo *tmp)
{
	tmp = histo;
	while (tmp != NULL)
	{
		if (tmp->current)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	else if (tmp->prev == NULL)
	{
		tmp->current = 0;
		sh_free_string(line->string);
		line->string = first_space();
	}
	else
	{
		tmp->current = 0;
		tmp->prev->current = 1;
		sh_free_string(line->string);
		line->string = sh_dupline(tmp->prev->line);
	}
	sh_print_line(shell, line);
	line->lsize = sh_update_lsize(histo, tmp, 2);
}
