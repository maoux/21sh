/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 15:37:29 by heynard           #+#    #+#             */
/*   Updated: 2017/09/28 15:37:30 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void			sh_window_resize(int sig)
{
	t_shell		*shell;

	shell = sh_call_shell();
	if (shell)
		ioctl(0, TIOCGWINSZ, shell->win_size);
}

void			sh_ctr_c(int sig)
{
	t_shell		*shell;

	shell = sh_call_shell();
	if (shell)
	{
		sh_remove_cursor(shell->line);
		sh_print_line(shell, shell->line);
		write(STDOUT_FILENO, "\n", 1);
		sh_free_line(shell->line);
		sh_init_line(shell, shell->line);
		sh_prompt(shell);
		tputs(tgetstr("sc", NULL), 1, ft_putcharint);
		sh_print_string(shell->line);
	}
}

void			sh_handle_sigkill(void)
{
	t_shell		*shell;

	shell = sh_call_shell();
	if (shell)
	{
		if (shell->line)
		{
			sh_remove_cursor(shell->line);
			sh_free_line(shell->line);
		}
		ft_dprintf(STDOUT_FILENO, "\n");
		sh_run_save_config(shell);
		shell->env ? sh_free_env(shell->env) : (0);
		exit(shell->exit_value);
	}
}

void			sh_check_signal(int sig)
{
	if (sig == SIGKILL)
		sh_handle_sigkill();
	if (sig == SIGQUIT)
		sh_suspended(sig);
	if (sig == SIGTERM)
		sh_suspended(sig);
}

void			sh_suspended(int sig)
{
	return ;
}
