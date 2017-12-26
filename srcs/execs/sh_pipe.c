/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 15:16:18 by heynard           #+#    #+#             */
/*   Updated: 2017/12/26 15:16:21 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static void			sh_pipe_child_left(t_shell *shell, t_ast *ast, int pde[2])
{
	dup2(pde[1], STDOUT_FILENO);
	close(pde[0]);
	sh_exec_tree(shell, ast->left);
	exit(shell->exit_value);
}

static void			sh_pipe_child_right(t_shell *shell, t_ast *ast, int pde[2])
{
	dup2(pde[0], STDIN_FILENO);
	close(pde[1]);
	sh_exec_tree(shell, ast->right);
	exit(shell->exit_value);
}

void				sh_exec_pipe(t_shell *shell, t_ast *ast)
{
	int				pde[2];
	int				pid[2];

	if (pipe(pde) != 0)
		ft_putendl_fd("21sh: unable to pipe\n", STDERR_FILENO);
	else
	{
		if ((pid[0] = fork()) == 0)
			sh_pipe_child_left(shell, ast, pde);
		if ((pid[1] = fork()) == 0)
			sh_pipe_child_right(shell, ast, pde);
		close(pde[0]);
		close(pde[1]);
		signal(SIGINT, sh_get_sigint_pipe);
		waitpid(pid[0], 0, 0);
		shell->exit_value = waitpid(pid[1], 0, 0);
	}
}
