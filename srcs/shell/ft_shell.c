/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 16:26:08 by heynard           #+#    #+#             */
/*   Updated: 2017/09/06 16:26:09 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void			sh_alter_lst(t_shell *shell, t_token *list,
								char *buf, char *buf2)
{
	t_token		*tmp;

	tmp = list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, "~", 1))
		{
			if (sh_get_var_env(shell->env, "HOME"))
			{
				buf2 = ft_strrcpy_spec(tmp->str, '~');
				ft_strdel(&tmp->str);
				buf = ft_strdup(sh_get_var_env(shell->env, "HOME"));
				if (buf2)
					tmp->str = ft_strjoin(buf, buf2);
				else
					tmp->str = ft_strdup(buf);
				ft_strdel(&buf);
				ft_strdel(&buf2);
			}
		}
		if (ft_strchr(tmp->str, '$'))
			sh_alter_lst_venv(shell, tmp, 0, NULL);
		tmp = tmp->next;
	}
}

void			ft_shell(t_shell *shell, t_line *line)
{
	t_token		*list;
	char		*command;

	if (!(command = sh_create_string(line)))
		return ;
	list = sh_lexer((const char *)command, 0, ft_strlen(command));
	sh_alter_lst(shell, list, NULL, NULL);
	sh_parse_lst(shell, list, NULL);
	free_lst(list);
	ft_strdel(&command);
}
