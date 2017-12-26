/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_call_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:59:16 by heynard           #+#    #+#             */
/*   Updated: 2017/11/13 12:59:17 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

t_shell					*sh_call_shell(void)
{
	static t_shell		*shell = NULL;

	if (shell == NULL)
	{
		if (!(shell = malloc(sizeof(t_shell))))
			return (NULL);
		shell->nbl = 0;
		shell->exit_builtin = 0;
		shell->exit_value = 0;
		shell->histo = NULL;
		shell->line = NULL;
	}
	return (shell);
}
