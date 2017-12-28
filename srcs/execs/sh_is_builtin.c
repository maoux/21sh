/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 18:25:31 by heynard           #+#    #+#             */
/*   Updated: 2017/12/28 18:26:01 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

int					sh_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (2);
	else if (!ft_strcmp(cmd, "env"))
		return (3);
	else if (!ft_strcmp(cmd, "exit"))
		return (4);
	else if (!ft_strcmp(cmd, "setenv"))
		return (5);
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (6);
	return (0);
}

void				sh_launch_builtin(t_shell *shell, char **av, t_ast *node)
{
	if (!ft_strcmp(av[0], "cd"))
		sh_builtin_cd(shell, count_argv(av), av);
	else if (!ft_strcmp(av[0], "exit"))
		sh_builtin_exit(shell, count_argv(av), av);
	else if (!ft_strcmp(av[0], "setenv"))
		sh_builtin_setenv(shell, count_argv(av), av);
	else if (!ft_strcmp(av[0], "unsetenv"))
		sh_builtin_unsetenv(shell, count_argv(av), av);
}

void				sh_solve_redirection(t_shell *shell, t_ast *node)
{
	t_redirection	*tmp;

	tmp = node->redirection;
	while (tmp)
	{
		if (sh_handle_redirection(shell, node, tmp) < 0)
			exit(EXIT_FAILURE);
		tmp = tmp->next;
	}
}
