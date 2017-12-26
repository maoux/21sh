/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 12:39:21 by heynard           #+#    #+#             */
/*   Updated: 2017/12/16 12:39:35 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void				sh_free_heredoc(t_heredoc *tmp)
{
	t_heredoc		*to_free;

	while (tmp)
	{
		to_free = tmp;
		tmp = tmp->next;
		ft_strdel(&(to_free->str));
		free(to_free);
	}
}

void				sh_get_sigint_heredoc(int sig)
{
	t_shell			*shell;

	shell = sh_call_shell();
	if (shell)
	{
		sh_remove_cursor(shell->heredoc);
		sh_print_line(shell, shell->heredoc);
		write(STDOUT_FILENO, "\n", 1);
		sh_heredoc_prompt(shell);
		sh_free_line(shell->heredoc);
		sh_init_line(shell, shell->heredoc);
		tputs(tgetstr("sc", NULL), 1, ft_putcharint);
		sh_print_string(shell->heredoc);
	}
}

void				sh_start_heredoc(t_shell *shell, int *test,
										t_line *current, long int *key)
{
	sh_init_line(shell, current);
	sh_heredoc_prompt(shell);
	signal(SIGINT, sh_get_sigint_heredoc);
	tputs(tgetstr("sc", NULL), 1, ft_putcharint);
	*key = 0;
	sh_print_string(current);
	shell->heredoc = current;
	*test = 1;
}

int					sh_end_heredoc(t_line *current, t_redirection *redir,
									t_heredoc **tmp)
{
	char			*str;

	str = sh_create_string(current);
	if (str)
	{
		if (!ft_strcmp(str, redir->param))
		{
			ft_strdel(&str);
			return (0);
		}
	}
	*tmp = sh_add_heredoc(current, *tmp, str);
	sh_free_line(current);
	return (1);
}

t_heredoc			*sh_handle_heredoc(t_shell *shell, t_redirection *redir,
										long int key, int test)
{
	t_line			current;
	t_heredoc		*tmp;
	int				fd;

	tmp = NULL;
	while (TRUE)
	{
		sh_start_heredoc(shell, &test, &current, &key);
		while (key != KEY_RETURN && key != 4 && test)
		{
			key = 0;
			test = read(0, &key, 8);
			sh_key_event(shell, &current, key);
		}
		sh_remove_cursor(&current);
		sh_print_line(shell, &current);
		ft_dprintf(STDOUT_FILENO, "\n");
		if (key == 4 || test == 0)
			break ;
		if (sh_end_heredoc(&current, redir, &tmp) == 0)
			break ;
	}
	sh_free_line(&current);
	shell->line = NULL;
	return (tmp);
}
