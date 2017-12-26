/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 15:49:33 by heynard           #+#    #+#             */
/*   Updated: 2017/08/02 15:49:34 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"
#include "../../includes/linediting.h"

void				sh_print_error(int fd, const char *error)
{
	if (fd == 0)
		ft_dprintf(STDERR_FILENO, "%s%s%s\n", RED, error, CLEAR);
	else
		ft_dprintf(fd, "%s%s%s\n", RED, error, CLEAR);
}
