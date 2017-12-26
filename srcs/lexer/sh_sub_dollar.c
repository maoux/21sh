/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_sub_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:42:29 by heynard           #+#    #+#             */
/*   Updated: 2017/11/17 15:42:30 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static char		*sh_swap_pid(char *res)
{
	char		*tmpbuf;
	char		*tmppid;

	tmpbuf = NULL;
	if (res == NULL)
		res = ft_itoa((int)getpid());
	else
	{
		tmpbuf = res;
		tmppid = ft_itoa((int)getpid());
		res = ft_strjoin(res, tmppid);
		ft_strdel(&tmpbuf);
		ft_strdel(&tmppid);
	}
	return (res);
}

static char		*sh_swap_var_env(char *res, char *var)
{
	char		*tmpbuf;

	tmpbuf = NULL;
	if (res == NULL)
		res = ft_strdup(var);
	else
	{
		tmpbuf = res;
		res = ft_strjoin(res, var);
		ft_strdel(&tmpbuf);
	}
	return (res);
}

static char		*sh_swap_default(char *res, char **buf, int i)
{
	char		*tmpbuf;

	tmpbuf = NULL;
	if (res == NULL)
		res = ft_strdup(buf[i]);
	else
	{
		tmpbuf = res;
		res = ft_strjoin(res, buf[i]);
		ft_strdel(&tmpbuf);
	}
	return (res);
}

static char		*sh_swap_last_dollar(char *res)
{
	char		*tmpbuf;

	tmpbuf = res;
	res = ft_strjoin(res, "$");
	ft_strdel(&tmpbuf);
	return (res);
}

void			sh_alter_lst_venv(t_shell *shell, t_token *tmp,
									int i, char *res)
{
	char		**buf;
	char		*var;

	buf = ft_strsplit_sh(tmp->str);
	while (buf[i])
	{
		if (i == 0 && tmp->str[0] != '$')
			res = ft_strdup(buf[i]);
		else if (!ft_strcmp(buf[i], "$$"))
			res = sh_swap_pid(res);
		else if ((var = sh_get_var_env(shell->env, buf[i] + 1)) &&
					buf[i][0] == '$')
			res = sh_swap_var_env(res, var);
		else if (buf[i][0] != '$')
			res = sh_swap_default(res, buf, i);
		else if (buf[i][0] == '$' && buf[i][1] == '\0' && buf[i + 1] == NULL)
			res = sh_swap_last_dollar(res);
		i++;
	}
	i = 0;
	while (buf[i])
		ft_strdel(&buf[i++]);
	free(buf);
	ft_strdel(&tmp->str);
	tmp->str = res ? res : ft_strdup("");
}
