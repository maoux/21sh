/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 23:42:35 by heynard           #+#    #+#             */
/*   Updated: 2017/11/30 23:42:36 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

t_ast		*sh_parser_words(t_ast *ast, t_token **tmp, int *error)
{
	t_token	*first;

	first = (*tmp);
	while ((*tmp) && !is_binary_operator((*tmp)->type) && (*tmp)->type != SEMI)
		(*tmp) = (*tmp)->next;
	ast = sh_parser_word((*tmp), first, ast, error);
	return (ast);
}

t_ast		*sh_parser_word(t_token *tmp, t_token *first,
							t_ast *ast, int *error)
{
	t_ast	*tmp_tree;
	t_shell	*shell;

	shell = sh_call_shell();
	if (!ast)
	{
		if ((ast = sh_create_first_node(shell, first, error)) == NULL)
			return (NULL);
	}
	else if (is_binary_operator(ast->type) || ast->type == SEMI)
	{
		tmp_tree = ast;
		while (tmp_tree->right)
			tmp_tree = tmp_tree->right;
		if (!(tmp_tree = sh_create_right_node(shell, first, tmp_tree, error)))
			sh_free_ast(ast);
	}
	else
	{
		if ((ast = sh_create_left_node(shell, first, ast, error)) == NULL)
			sh_free_ast(ast);
	}
	return (ast);
}
