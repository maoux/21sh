/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_create_node_ast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 23:35:16 by heynard           #+#    #+#             */
/*   Updated: 2017/11/30 23:35:28 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static t_ast		*error_node_creation(t_ast *node)
{
	if (node)
		free(node);
	return (NULL);
}

t_ast				*sh_create_first_node(t_shell *shell,
										t_token *first, int *error)
{
	t_ast			*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = COMMAND;
	node->redirection = create_redirection_list(shell, first, error);
	if (*error == 1)
		return (error_node_creation(node));
	node->av = create_argv_tab(first, 0, first);
	if (!node->av)
	{
		ft_dprintf(STDERR_FILENO, "21sh, memory allocation failed\n");
		free(node);
		return (NULL);
	}
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast				*sh_create_right_node(t_shell *shell, t_token *first,
											t_ast *ast,
											int *error)
{
	t_ast			*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		ft_dprintf(STDERR_FILENO, "21sh, memory allocation failed\n");
		sh_free_ast(ast);
		return (NULL);
	}
	node->type = COMMAND;
	node->redirection = create_redirection_list(shell, first, error);
	if (*error == 1)
		return (error_node_creation(node));
	node->av = create_argv_tab(first, 0, first);
	if (!node->av)
	{
		ft_dprintf(STDERR_FILENO, "21sh, memory allocation failed\n");
		sh_free_ast(ast);
		free(node);
		return (NULL);
	}
	node->left = NULL;
	node->right = NULL;
	ast->right = node;
	return (ast);
}

t_ast				*sh_create_left_node(t_shell *shell,
										t_token *first,
										t_ast *ast,
										int *error)
{
	t_ast			*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		ft_dprintf(STDERR_FILENO, "21sh, memory allocation failed\n");
		sh_free_ast(ast);
		return (NULL);
	}
	node->type = COMMAND;
	node->redirection = create_redirection_list(shell, first, error);
	if (*error == 1)
		return (error_node_creation(node));
	node->av = create_argv_tab(first, 0, first);
	if (!node->av)
	{
		ft_dprintf(STDERR_FILENO, "21sh, memory allocation failed\n");
		sh_free_ast(ast);
		free(node);
		return (NULL);
	}
	node->left = ast;
	node->right = NULL;
	return (node);
}

t_ast				*sh_create_operator_node(t_token *tmp, t_ast *ast)
{
	t_ast			*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		ft_dprintf(STDERR_FILENO, "21sh, memory allocation failed\n");
		sh_free_ast(ast);
		return (NULL);
	}
	node->type = tmp->type;
	node->av = NULL;
	node->redirection = NULL;
	node->left = ast;
	node->right = NULL;
	return (node);
}
