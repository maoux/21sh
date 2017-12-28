/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 15:16:32 by heynard           #+#    #+#             */
/*   Updated: 2017/12/26 15:16:33 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

int					sh_is_fd(char *param)
{
	int				i;

	i = 0;
	while (param[i] != '\0')
	{
		if (!ft_isdigit(param[i]))
			return (0);
		i++;
	}
	return (1);
}

int					sh_solve_heredoc(t_shell *shell, t_ast *node,
									t_redirection *redir)
{
	t_heredoc		*tmp;
	int				pde[2];
	int				pid;

	if (pipe(pde) != 0)
		ft_putendl_fd("21sh: unable to pipe\n", STDERR_FILENO);
	else
	{
		if ((pid = fork()) == 0)
		{
			dup2(pde[1], STDOUT_FILENO);
			close(pde[0]);
			tmp = redir->heredoc;
			while (tmp)
			{
				ft_dprintf(STDOUT_FILENO, "%s\n", tmp->str);
				tmp = tmp->next;
			}
			exit(shell->exit_value);
		}
		waitpid(pid, 0, 0);
		dup2(pde[0], STDIN_FILENO);
		close(pde[1]);
	}
	return (1);
}

int					sh_handle_greatand(t_shell *shell, t_ast *node,
										t_redirection *redir)
{
	if (redir->closed && redir->type == GREATAND)
	{
		if (redir->fd == 2)
			close(redir->fd);
		else if (redir->fd < 2)
			close(STDOUT_FILENO);
		if (redir->fd == 2)
			shell->err_closed = 1;
		return (1);
	}
	else if (redir->type == GREATAND && sh_is_fd(redir->param))
		return (sh_greatand_param(shell, redir));
	else if (redir->type == GREATAND && redir->fd == 2)
	{
		ft_dprintf(STDERR_FILENO,
					"21sh: %s: ambiguous redirect\n", redir->param);
		exit(1);
	}
	else if (redir->type == GREATAND)
		return (sh_greatand_simple(redir));
	return (0);
}

int					sh_handle_redirection(t_shell *shell, t_ast *node,
											t_redirection *redir)
{
	if (redir->type == GREATAND)
		return (sh_handle_greatand(shell, node, redir));
	if (redir->type == DLESS)
		return (sh_solve_heredoc(shell, node, redir));
	if (redir->type == GREAT || redir->type == GREATAND)
		redir->target_fd = open(redir->param,
								O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->type == GREATPIPE)
		redir->target_fd = open(redir->param,
								O_WRONLY | O_CREAT | O_TRUNC | O_SYMLINK, 0644);
	if (redir->type == DGREAT)
		redir->target_fd = open(redir->param,
								O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->type == LESS)
		redir->target_fd = open(redir->param, O_RDONLY);
	if (redir->target_fd < 0)
	{
		ft_dprintf(STDERR_FILENO,
						"21sh: %s: No such file or directory\n", redir->param);
		return (-1);
	}
	else
		dup2(redir->target_fd, redir->fd);
	close(redir->target_fd);
	return (1);
}
