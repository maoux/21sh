/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:04:13 by heynard           #+#    #+#             */
/*   Updated: 2017/07/31 14:04:15 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static void				sh_margin_intro(t_shell *shell)
{
	int					i;

	i = 0;
	while (i < shell->win_size->ws_col / 2 - 15)
	{
		ft_dprintf(STDOUT_FILENO, " ");
		i++;
	}
}

static void				sh_intro(t_shell *shell)
{
	sh_margin_intro(shell);
	ft_dprintf(STDOUT_FILENO,
		"%s _____   ___    _____  _   _  \n%s", BLUE2, CLEAR);
	sh_margin_intro(shell);
	ft_dprintf(STDOUT_FILENO,
		"%s/___  \\ |_  | /  ___/ | | | |\n%s", BLUE, CLEAR);
	sh_margin_intro(shell);
	ft_dprintf(STDOUT_FILENO,
		"%s ___| |   | | | |___  | |_| | \n%s", BLUE3, CLEAR);
	sh_margin_intro(shell);
	ft_dprintf(STDOUT_FILENO,
		"%s/  ___/   | | \\___  \\ |  _  | \n%s", CYAN3, CLEAR);
	sh_margin_intro(shell);
	ft_dprintf(STDOUT_FILENO,
		"%s| |___    | |  ___| | | | | | \n%s", CYAN, CLEAR);
	sh_margin_intro(shell);
	ft_dprintf(STDOUT_FILENO,
		"%s|_____|   |_| /_____/ |_| |_| \n\n%s", CYAN2, CLEAR);
}

static void				sh_main_loop(t_shell *shell, int test,
										long key, t_line line)
{
	if (!shell->simple_mode && shell->win_size->ws_col > 30)
		sh_intro(shell);
	while (TRUE)
	{
		key = 0;
		sh_prepare_line(shell, &line);
		while ((key != 4 || line.lsize > 1) && key != KEY_RETURN &&
				test > 0 && shell->exit_builtin == 0)
		{
			key = 0;
			test = read(STDIN_FILENO, &key, 8);
			sh_key_event(shell, &line, key);
		}
		if ((key == 4 && line.lsize == 1) || test == 0)
			break ;
		sh_treat_line(shell, &line);
		if (shell->exit_builtin)
			break ;
	}
	sh_end_main(shell, &line);
	if (!shell->exit_builtin)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	sh_run_save_config(shell);
}

int						main(int ac, char **av)
{
	t_line				line;
	t_shell				*shell;
	extern char			**environ;

	tputs(tgetstr("vi", NULL), 1, ft_putcharint);
	shell = sh_call_shell();
	if (!shell)
	{
		ft_dprintf(STDERR_FILENO,
				"21sh: First memory allocation failed, unable to run shell\n");
		return (1);
	}
	sh_init_env(environ, shell);
	sh_init_env2(shell);
	shell->exit_value = 0;
	sh_prepare_shell(shell);
	if (sh_get_var_env(shell->env, "TERM") == NULL || shell->simple_mode)
		sh_alternative_shell(shell);
	else
	{
		sh_run_term_config(shell);
		sh_main_loop(shell, 1, 0, line);
	}
	shell->env ? sh_free_env(shell->env) : (0);
	return (shell->exit_value);
}
