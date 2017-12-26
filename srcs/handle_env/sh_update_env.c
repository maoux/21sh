/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_update_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 20:25:45 by heynard           #+#    #+#             */
/*   Updated: 2017/06/27 21:12:44 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"
#include "../../libft/includes/libft.h"

t_var_env			*sh_add_to_env(t_shell *shell, char *name, char *value)
{
	t_var_env		*tmp;
	t_var_env		*new;

	if ((new = sh_malloc_env(shell)) == NULL)
		return (shell->env);
	new->name = ft_strdup(name ? name : "");
	new->value = ft_strdup(value ? value : "");
	tmp = shell->env;
	if (shell->env == NULL)
		return (new);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (shell->env);
}

t_var_env			*sh_update_env(t_shell *shell, char *name, char *value)
{
	t_var_env		*tmp;
	char			*to_free;

	tmp = shell->env;
	to_free = NULL;
	if (tmp == NULL)
		return (shell->env = sh_add_to_env(shell, name, value));
	while (tmp && ft_strcmp(name, tmp->name))
		tmp = tmp->next;
	if (tmp)
	{
		to_free = tmp->value;
		tmp->value = ft_strdup(value);
		free(to_free);
	}
	else
		shell->env = sh_add_to_env(shell, name, value);
	return (shell->env);
}
