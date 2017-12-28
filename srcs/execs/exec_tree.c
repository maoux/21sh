/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 19:11:06 by heynard           #+#    #+#             */
/*   Updated: 2017/12/05 19:11:07 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void				sh_exec_bin(t_shell *shell, const char *path,
								char **av, t_ast *node)
{
	pid_t			pid;
	char			**environ;
	t_redirection	*tmp;

	environ = sh_swapenv_to_char(shell->env);
	if ((pid = fork()) == 0)
	{
		tmp = node->redirection;
		while (tmp)
		{
			if (sh_handle_redirection(shell, node, tmp) < 0)
				exit(EXIT_FAILURE);
			tmp = tmp->next;
		}
		if (execve(path, av, environ) == -1)
			sh_error_execve(path, environ);
	}
	else if (pid == -1)
		ft_putendl_fd("21sh: cannot create processus.", 2);
	shell->exit_value = sh_wait_child(pid);
	free_argv_tab(environ);
}

int					sh_exec_builtin(t_shell *shell, char **av, t_ast *node)
{
	pid_t			pid;
	t_redirection	*tmp;
	int				builtin;

	if ((builtin = sh_is_builtin(av[0])))
	{
		if ((pid = fork()) == 0)
		{
			sh_solve_redirection(shell, node);
			if (!ft_strcmp(av[0], "echo"))
				sh_builtin_echo(count_argv(av), av);
			else if (!ft_strcmp(av[0], "env"))
				sh_builtin_env(shell, count_argv(av), av, node);
			exit(EXIT_SUCCESS);
		}
		else if (pid < 0)
			return (0);
		shell->exit_value = sh_wait_child(pid);
		sh_launch_builtin(shell, av, node);
		shell->exit_builtin = builtin == 4 ? 1 : 0;
		return (0);
	}
	return (1);
}

void				sh_solve_simple_command(t_shell *shell, t_ast *node)
{
	t_redirection	*tmp;
	int				pid;

	if ((pid = fork()) == 0)
	{
		tmp = node->redirection;
		while (tmp)
		{
			if (sh_handle_redirection(shell, node, tmp) < 0)
				exit(EXIT_FAILURE);
			tmp = tmp->next;
		}
		exit(EXIT_SUCCESS);
	}
	else if (pid == -1)
		ft_putendl_fd("21sh: cannot create processus.", 2);
	shell->exit_value = sh_wait_child(pid);
}

void				sh_handle_command(t_shell *shell, char **av, t_ast *node)
{
	struct stat		buffer;

	if (av && av[0] != NULL)
	{
		if (sh_exec_builtin(shell, av, node) == 0)
			return ;
		if (stat(av[0], &buffer) == 0)
			sh_exec_bin(shell, av[0], av, node);
		else
			sh_path_finding(shell, av, node);
	}
	else
		sh_solve_simple_command(shell, node);
}

void				sh_exec_tree(t_shell *shell, t_ast *ast)
{
	if (ast->type == PIPE)
		sh_exec_pipe(shell, ast);
	else if (ast->left)
		sh_exec_tree(shell, ast->left);
	if (ast->type == COMMAND)
		sh_handle_command(shell, ast->av, ast);
	else if (ast->type == AND_IF && !shell->exit_value)
		sh_exec_tree(shell, ast->right);
	else if (ast->type == OR_IF && shell->exit_value)
		sh_exec_tree(shell, ast->right);
	else if (ast->type != PIPE && ast->type != OR_IF &&
			ast->type != AND_IF && ast->right)
		sh_exec_tree(shell, ast->right);
}
