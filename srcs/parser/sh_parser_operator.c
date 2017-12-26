/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 00:14:18 by heynard           #+#    #+#             */
/*   Updated: 2017/12/01 00:14:18 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

t_ast			*sh_parser_semi(t_ast *ast, t_token **tmp)
{
	ast = sh_create_operator_node((*tmp), ast);
	while ((*tmp) && (*tmp)->type == SEMI)
		(*tmp) = (*tmp)->next;
	return (ast);
}

t_ast			*sh_parser_operator(t_ast *ast, t_token **tmp)
{
	if ((ast->type == OR_IF || ast->type == AND_IF ||
		ast->type == SEMI) && (*tmp)->type == PIPE)
		ast->right = sh_create_operator_node((*tmp), ast->right);
	else
		ast = sh_create_operator_node((*tmp), ast);
	(*tmp) = (*tmp)->next;
	return (ast);
}
