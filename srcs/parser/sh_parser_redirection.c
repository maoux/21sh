/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 23:50:38 by heynard           #+#    #+#             */
/*   Updated: 2017/11/30 23:50:39 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

t_redirection			*inner_add_redirection(t_redirection *n,
												t_redirection *lst)
{
	t_redirection		*tmp;

	if (lst == NULL)
		return (n);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = n;
	return (lst);
}

t_redirection			*add_redirection_to_list(t_shell *shell, t_token *tmp,
													t_redirection *lst)
{
	t_redirection		*n;

	if ((n = malloc(sizeof(t_redirection))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: memory allocation failed\n");
		return (lst);
	}
	n->type = tmp->type;
	n->param = ft_strdup(tmp->next->str);
	if (ft_isdigit(tmp->str[0]))
		n->fd = (int)(tmp->str[0] - 48);
	else if (n->type == LESS || n->type == DLESS || n->type == GREATAND)
		n->fd = STDIN_FILENO;
	else
		n->fd = STDOUT_FILENO;
	n->next = NULL;
	if (!ft_strcmp("-", n->param))
		n->closed = 1;
	else
		n->closed = 0;
	if (n->type == DLESS)
		n->heredoc = sh_handle_heredoc(shell, n, 0, 1);
	else
		n->heredoc = NULL;
	return (inner_add_redirection(n, lst));
}

void					free_redirection_list(t_redirection *list)
{
	t_redirection		*tmp;

	if (list)
	{
		while (list)
		{
			tmp = list;
			list = list->next;
			if (tmp->param)
				ft_strdel(&(tmp->param));
			if (tmp->heredoc)
				sh_free_heredoc(tmp->heredoc);
			free(tmp);
		}
	}
}

t_redirection			*error_add_redirection(int *error, t_redirection *lst,
												t_token *tmp)
{
	ft_dprintf(STDERR_FILENO,
			"21sh: parse error near '%s'\n", tmp->str);
	free_redirection_list(lst);
	(*error) = 1;
	return (NULL);
}

t_redirection			*create_redirection_list(t_shell *shell,
												t_token *first, int *error)
{
	t_redirection		*lst;
	t_token				*tmp;

	lst = NULL;
	tmp = first;
	while (tmp && !is_binary_operator(tmp->type) && tmp->type != SEMI)
	{
		if (is_redirection_operator(tmp->type) && tmp->next != NULL &&
			tmp->next->type == WORD)
		{
			lst = add_redirection_to_list(shell, tmp, lst);
			tmp = tmp->next;
		}
		else if (is_redirection_operator(tmp->type))
			return (error_add_redirection(error, lst, tmp));
		tmp = tmp->next;
	}
	if (*error == 1)
	{
		free_redirection_list(lst);
		return (NULL);
	}
	return (lst);
}
