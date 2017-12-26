/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 14:53:44 by heynard           #+#    #+#             */
/*   Updated: 2017/06/27 20:58:01 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"
#include "../../libft/includes/libft.h"

char					*sh_get_var_env(t_var_env *env, const char *name)
{
	t_var_env			*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void					sh_print_env(t_var_env *env)
{
	t_var_env			*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		ft_printf("%s=%s\n", tmp->name, (tmp->value ? tmp->value : ""));
		tmp = tmp->next;
	}
}

void					sh_free_env(t_var_env *env)
{
	t_var_env			*tmp;

	tmp = env;
	while (env)
	{
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		tmp = env;
	}
}

t_var_env				*sh_malloc_env(t_shell *shell)
{
	t_var_env			*new;

	if ((new = malloc(sizeof(t_var_env))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: memory allocation failed\n");
		shell->malloc_error = 1;
		return (NULL);
	}
	new->name = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

t_var_env				*sh_copy_environ(char **environ, t_shell *shell,
											t_var_env *tmp, t_var_env *new)
{
	unsigned int		i;

	i = 0;
	if (!environ || !(*environ))
		return (NULL);
	if ((shell->env = sh_malloc_env(shell)) == NULL)
		return (NULL);
	shell->env->name = ft_strcpy_spec(environ[i], '=');
	shell->env->value = ft_strrcpy_spec(environ[i++], '=');
	tmp = shell->env;
	while (environ && environ[i])
	{
		if ((new = sh_malloc_env(shell)) == NULL)
			return (shell->env);
		new->name = ft_strcpy_spec(environ[i], '=');
		new->value = ft_strrcpy_spec(environ[i++], '=');
		tmp->next = new;
		tmp = tmp->next;
	}
	return (shell->env);
}
