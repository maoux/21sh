/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 15:23:03 by heynard           #+#    #+#             */
/*   Updated: 2017/12/26 15:23:04 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void				sh_get_sigint(int sig)
{
	write(1, "\n", 1);
}

void				sh_get_sigint_pipe(int sig)
{
	return ;
}

int					sh_wait_child(pid_t pid)
{
	int				status;

	signal(SIGINT, sh_get_sigint);
	wait(&status);
	return (status);
}

int					count_argv(char **av)
{
	int				i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

void				sh_error_execve(const char *path, char **environ)
{
	ft_putstr_fd("21sh: permission denied: ", 2);
	ft_putendl_fd((char *)path, 2);
	free_argv_tab(environ);
	exit(EXIT_FAILURE);
}
