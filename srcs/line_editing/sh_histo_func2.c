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

static void		sh_print_line_histo(t_shell *shell, t_line *line)
{
	tputs(tgetstr("rc", NULL), 1, ft_putcharint);
	tputs(tgetstr("cd", NULL), 1, ft_putcharint);
	tputs(tgetstr("sc", NULL), 1, ft_putcharint);
	sh_print_string(line);
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

void			sh_move_up_histo(t_shell *shell, t_line *line, t_histo *histo,
									t_histo *tmp)
{
	if (!histo)
		return ;
	tmp = histo;
	while (tmp != NULL)
	{
		if (tmp->current)
			break ;
		tmp = tmp->next;
	}
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
	sh_print_line_histo(shell, line);
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
	sh_print_line_histo(shell, line);
	line->lsize = sh_update_lsize(histo, tmp, 2);
}
