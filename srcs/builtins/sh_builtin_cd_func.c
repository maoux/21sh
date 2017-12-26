/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 16:47:52 by heynard           #+#    #+#             */
/*   Updated: 2017/12/12 21:30:47 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

void				sh_handle_cd_env(t_shell *shell, char *curpath)
{
	char			*pwd;

	pwd = sh_get_var_env(shell->env, "PWD");
	if (pwd)
		sh_update_env(shell, "OLDPWD", pwd);
	sh_update_env(shell, "PWD", curpath);
	shell->exit_value = 0;
}

void				sh_handle_cd_env_link(t_shell *shell, char *curpath)
{
	char			*buffer;
	char			*pwd;

	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if (buffer == NULL)
	{
		ft_putendl_fd("21sh: cannot find current directory", 2);
		return ;
	}
	pwd = sh_get_var_env(shell->env, "PWD");
	if (pwd)
		sh_update_env(shell, "OLDPWD", pwd);
	sh_update_env(shell, "PWD", buffer);
	ft_strdel(&buffer);
	shell->exit_value = 0;
}

char				*sh_catpath(t_shell *shell, const char *dir)
{
	char			*tmp;
	char			*pwd;

	pwd = NULL;
	pwd = sh_get_var_env(shell->env, "PWD");
	if (pwd)
	{
		tmp = ft_strjoin(pwd, "/");
		shell->curpath = ft_strjoin(tmp, dir);
		free(tmp);
		return (shell->curpath);
	}
	shell->exit_value = 1;
	return (NULL);
}
