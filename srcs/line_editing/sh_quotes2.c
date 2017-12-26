/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quotes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:49:27 by heynard           #+#    #+#             */
/*   Updated: 2017/12/15 18:49:47 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void			sh_ctr_c_quotes(int sig)
{
	t_shell			*shell;

	shell = sh_call_shell();
	if (shell)
	{
		sh_remove_cursor(shell->quotes);
		sh_print_line(shell, shell->quotes);
		write(STDOUT_FILENO, "\n", 1);
		sh_quote_prompt(shell, shell->q);
		sh_free_line(shell->quotes);
		sh_init_line(shell, shell->quotes);
		tputs(tgetstr("sc", NULL), 1, ft_putcharint);
		sh_print_string(shell->quotes);
	}
}

void			sh_quote_prompt(t_shell *shell, char q)
{
	shell->prompt_size = 7;
	if (q == '\"')
		ft_dprintf(STDOUT_FILENO, "dquote> ");
	else if (q == '\'')
		ft_dprintf(STDOUT_FILENO, "squote> ");
}

void			sh_prepare_line_quotes(t_shell *shell, t_line *line,
										char q, t_line *current)
{
	line->string = sh_add_end(line->string, '\n');
	line->lsize++;
	shell->q = q;
	signal(SIGINT, sh_ctr_c_quotes);
	sh_init_line(shell, current);
	shell->quotes = current;
	sh_quote_prompt(shell, q);
	tputs(tgetstr("sc", NULL), 1, ft_putcharint);
}
