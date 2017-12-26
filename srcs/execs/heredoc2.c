/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 17:17:13 by heynard           #+#    #+#             */
/*   Updated: 2017/12/26 17:17:14 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void				sh_heredoc_prompt(t_shell *shell)
{
	shell->prompt_size = 9;
	ft_dprintf(STDOUT_FILENO, "heredoc> ");
}

t_heredoc			*sh_add_heredoc(t_line *current, t_heredoc *tmp, char *s)
{
	t_heredoc		*end;
	t_heredoc		*new;

	if ((new = malloc(sizeof(t_heredoc))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: memory allocation failed\n");
		return (tmp);
	}
	if (s)
		new->str = s;
	else
		new->str = ft_strdup("");
	new->next = NULL;
	if (!tmp)
		return (new);
	end = tmp;
	while (end->next)
		end = end->next;
	end->next = new;
	return (tmp);
}
