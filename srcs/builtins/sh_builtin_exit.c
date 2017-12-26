/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 21:17:33 by heynard           #+#    #+#             */
/*   Updated: 2017/12/12 22:45:18 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static int	check_arg(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void		sh_builtin_exit(t_shell *shell, int ac, char **av)
{
	int		exit_value;

	if (ac > 2)
		ft_putendl_fd("exit: too many arguments", 2);
	else if (ac == 1)
		shell->exit_builtin = 1;
	else if (check_arg(av[1]) == 0)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else
	{
		shell->exit_value = ft_atoi(av[1]);
		shell->exit_builtin = 1;
	}
}
