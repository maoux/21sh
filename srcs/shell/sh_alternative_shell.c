/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_alternative_shell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 13:35:38 by heynard           #+#    #+#             */
/*   Updated: 2017/12/04 13:35:43 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void			sh_alternative_ctr_c(int sig)
{
	ft_putstr("\n$>");
}

static void		sh_alternative_shell_exec(t_shell *shell, char *command)
{
	t_token		*list;

	list = NULL;
	list = sh_lexer((const char *)command, 0, ft_strlen(command));
	if (list)
	{
		sh_parse_lst(shell, list, NULL);
		free_lst(list);
	}
}

void			sh_alternative_shell(t_shell *shell)
{
	char		*command;
	int			gnl;

	command = NULL;
	shell->simple_mode = 1;
	ft_putendl_fd(sh_get_var_env(shell->env, "PATH"), 0);
	while (TRUE)
	{
		signal(SIGINT, sh_alternative_ctr_c);
		if (shell->exit_builtin)
			break ;
		ft_putstr("$>");
		gnl = get_next_line(0, &command);
		if (ft_strequ(command, "exit") || !gnl)
		{
			!gnl ? ft_putendl("exit") : ft_strdel(&command);
			break ;
		}
		if (gnl < 0)
			ft_putendl_fd("21sh: read error\n", 2);
		else
			sh_alternative_shell_exec(shell, command);
		ft_strdel(&command);
	}
}
