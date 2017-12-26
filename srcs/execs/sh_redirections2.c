/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_redirections2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 17:39:53 by heynard           #+#    #+#             */
/*   Updated: 2017/12/26 17:39:54 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

int				sh_greatand_simple(t_redirection *redir)
{
	redir->target_fd = open(redir->param,
							O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(redir->target_fd, STDOUT_FILENO);
	dup2(redir->target_fd, STDERR_FILENO);
	close(redir->target_fd);
	return (1);
}

int				sh_greatand_param(t_shell *shell, t_redirection *redir)
{
	redir->target_fd = ft_atoi(redir->param);
	if (redir->target_fd > 2)
	{
		ft_dprintf(STDERR_FILENO,
				"21sh: %s: bad file descriptor\n", redir->param);
		exit(1);
	}
	if (redir->fd)
		dup2(redir->target_fd, redir->fd);
	else
	{
		dup2(redir->target_fd, STDOUT_FILENO);
		dup2(redir->target_fd, STDERR_FILENO);
	}
	if (redir->target_fd == 2 && shell->err_closed)
		close(redir->fd);
	return (1);
}
