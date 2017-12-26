/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_handle_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:01:24 by heynard           #+#    #+#             */
/*   Updated: 2017/11/13 14:05:10 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void					sh_prepare_line(t_shell *shell, t_line *line)
{
	sh_reset_histo(shell->histo);
	sh_prompt(shell);
	sh_init_line(shell, line);
	shell->line = line;
	tputs(tgetstr("sc", NULL), 1, ft_putcharint);
	sh_print_string(line);
	signal(SIGWINCH, sh_window_resize);
	signal(SIGINT, sh_ctr_c);
}

void					sh_treat_line(t_shell *shell, t_line *line)
{
	sh_remove_cursor(line);
	sh_print_line(shell, line);
	ft_dprintf(STDOUT_FILENO, "\n");
	sh_quote_line(shell, line);
	ft_shell(shell, line);
	tputs(tgetstr("sc", NULL), 1, ft_putcharint);
	shell->histo = sh_insert_histo(line, shell->histo);
	shell->line = NULL;
	sh_free_line(line);
	shell->nbl += 1;
}

void					sh_prepare_shell(t_shell *shell)
{
	signal(SIGWINCH, sh_window_resize);
	signal(SIGINT, sh_ctr_c);
	signal(SIGTERM, sh_check_signal);
	signal(SIGQUIT, sh_check_signal);
	signal(SIGKILL, sh_check_signal);
	signal(SIGTSTP, sh_suspended);
	signal(SIGSTOP, sh_suspended);
	sh_setup_terminal(shell);
}

void					sh_end_main(t_shell *shell, t_line *line)
{
	sh_remove_cursor(line);
	sh_print_line(shell, line);
	sh_free_line(line);
}
