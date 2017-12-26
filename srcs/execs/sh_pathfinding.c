/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pathfinding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 15:18:48 by heynard           #+#    #+#             */
/*   Updated: 2017/12/26 15:18:49 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void				sh_path_finding(t_shell *shell, char **av, t_ast *node)
{
	t_path_finding	pf;
	struct stat		buffer;

	shell->exit_value = 0;
	pf.current_path = sh_get_var_env(shell->env, "PATH");
	while (pf.current_path)
	{
		pf.next_path = ft_strchr(pf.current_path, ':');
		pf.next_path ? pf.next_path++ : (0);
		pf.tmp = ft_strjoin_spec(pf.current_path, "/", ':');
		pf.path = ft_strjoin(pf.tmp, av[0]);
		free(pf.tmp);
		if (stat(pf.path, &buffer) == 0)
		{
			sh_exec_bin(shell, pf.path, av, node);
			free(pf.path);
			return ;
		}
		free(pf.path);
		pf.current_path = pf.next_path;
	}
	ft_putstr_fd("21sh: command not found: ", 2);
	shell->exit_value = 1;
	ft_putendl_fd(av[0], 2);
}
