/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 20:39:55 by heynard           #+#    #+#             */
/*   Updated: 2017/12/12 23:19:28 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static void		sh_inner_builtin_unsetenv(t_shell *shell, const char *arg)
{
	t_var_env	*tmp;
	t_var_env	*prev;

	prev = shell->env;
	tmp = shell->env->next;
	while (tmp && ft_strcmp(tmp->name, arg))
	{
		prev = prev->next;
		tmp = tmp->next;
	}
	if (tmp)
	{
		prev->next = tmp->next;
		ft_strdel(&(tmp->name));
		ft_strdel(&(tmp->value));
		free(tmp);
	}
}

int				sh_builtin_unsetenv(t_shell *shell, int ac, char **av)
{
	t_var_env	*tmp;

	if (ac <= 1)
	{
		ft_putendl_fd("unsetenv: too few arguments", 2);
		return (1);
	}
	if (!ft_strcmp(shell->env->name, av[1]))
	{
		tmp = shell->env;
		shell->env = shell->env->next;
		ft_strdel(&(tmp->name));
		ft_strdel(&(tmp->value));
		free(tmp);
		return (0);
	}
	sh_inner_builtin_unsetenv(shell, av[1]);
	return (0);
}
