/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:38:58 by heynard           #+#    #+#             */
/*   Updated: 2017/09/07 15:38:59 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static void		sh_append_line(t_line *small, t_line *line)
{
	t_string	*tmp;

	tmp = small->string;
	while (tmp)
	{
		line->string = sh_add_end(line->string, tmp->value);
		line->lsize++;
		tmp = tmp->next;
	}
}

static int		sh_quote_in_string(t_string *str, char q)
{
	t_string	*tmp;

	tmp = str;
	if (!tmp)
		return (0);
	while (tmp != NULL)
	{
		if (tmp->value == q)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void		sh_end_quotes(t_shell *shell, t_line *current, t_line *line)
{
	sh_remove_cursor(current);
	sh_print_line(shell, current);
	ft_dprintf(STDOUT_FILENO, "\n");
	sh_append_line(current, line);
}

static void		sh_inner_quote_line(t_shell *shell, t_line *line, char q)
{
	t_line		current;
	long		key;
	int			test;

	while (TRUE)
	{
		sh_prepare_line_quotes(shell, line, q, &current);
		key = 0;
		sh_print_string(&current);
		test = 1;
		while (key != KEY_RETURN && test && key != 4)
		{
			key = 0;
			if (test == 0 || key == 4)
				break ;
			test = read(STDIN_FILENO, &key, 8);
			sh_key_event(shell, &current, key);
		}
		sh_end_quotes(shell, &current, line);
		if (sh_quote_in_string(current.string, q) || key == 4 || test == 0)
			break ;
		sh_free_line(&current);
	}
	sh_free_line(&current);
	sh_quote_line(shell, line);
}

void			sh_quote_line(t_shell *shell, t_line *line)
{
	t_string	*tmp;
	char		q;

	tmp = line->string;
	q = '\0';
	while (tmp)
	{
		if (tmp->value == '\'' || tmp->value == '"')
		{
			q = tmp->value;
			tmp = tmp->next;
			while (tmp->next && tmp->value != q)
				tmp = tmp->next;
			if (tmp->value == q)
				q = '\0';
		}
		tmp = tmp->next;
	}
	if (q != '\0')
		sh_inner_quote_line(shell, line, q);
}
