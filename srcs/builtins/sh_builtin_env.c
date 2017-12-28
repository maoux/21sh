/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 17:42:27 by heynard           #+#    #+#             */
/*   Updated: 2017/12/12 21:23:12 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static void			sh_fill_var_env(t_var_env *new, char *name, char *value)
{
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
}

static t_var_env	*sh_copy_env_temp(t_shell *shell)
{
	t_var_env		*tmpenv;
	t_var_env		*tmp2;
	t_var_env		*tmp;
	t_var_env		*new;

	tmp = shell->env;
	if (shell->env == NULL)
		return (NULL);
	if ((tmpenv = sh_malloc_env(shell)) == NULL)
		return (shell->env);
	sh_fill_var_env(tmpenv, tmp->name, tmp->value);
	tmp = tmp->next;
	tmp2 = tmpenv;
	while (tmp)
	{
		if ((new = sh_malloc_env(shell)) == NULL)
			return (shell->env);
		sh_fill_var_env(new, tmp->name, tmp->value);
		tmp2->next = new;
		tmp2 = tmp2->next;
		tmp = tmp->next;
	}
	return (tmpenv);
}

static void			sh_modify_tmp_env(t_shell *shell, char **av, int *i)
{
	char			*name;
	char			*value;

	name = ft_strcpy_spec(av[*i], '=');
	value = ft_strrcpy_spec(av[*i], '=');
	if (sh_get_var_env(shell->env, name))
		shell->env = sh_update_env(shell, name, value);
	else
		shell->env = sh_add_to_env(shell, name, value);
	ft_strdel(&name);
	ft_strdel(&value);
	(*i)++;
}

static void			sh_env_options(t_shell *shell, int *i, char **av)
{
	if (!ft_strcmp(av[*i], "-i"))
	{
		shell->env = NULL;
		(*i)++;
	}
	if (!ft_strcmp(av[*i], "--"))
	{
		shell->env = NULL;
		(*i)++;
	}
}

void				sh_builtin_env(t_shell *shell, int ac, char **av,
									t_ast *node)
{
	int				i;
	t_var_env		*tmpenv;
	char			*tmp;

	if (ac <= 1)
		sh_print_env(shell->env);
	else
	{
		i = 1;
		tmpenv = shell->env;
		sh_env_options(shell, &i, av);
		if (shell->env != NULL)
			shell->env = sh_copy_env_temp(shell);
		while (i < ac && (tmp = ft_strchr(av[i], '=')))
			sh_modify_tmp_env(shell, av, &i);
		if (i == ac)
			sh_print_env(shell->env);
		else
			sh_handle_command(shell, &av[i], node);
		sh_free_env(shell->env);
		shell->env = tmpenv;
	}
}
