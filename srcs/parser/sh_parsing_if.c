/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parsing_if.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 00:20:47 by heynard           #+#    #+#             */
/*   Updated: 2017/12/01 00:20:48 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

int				check_right_node(t_ast *ast, int ret)
{
	if (ast == NULL)
		return (0);
	if (ast->type == COMMAND)
		return (1);
	else
	{
		ret *= check_right_node(ast->left, ret);
		ret *= check_right_node(ast->right, ret);
		return (ret);
	}
}

int				sh_condition_operator(t_ast *ast, t_token *tmp)
{
	if ((is_binary_operator(tmp->type) && ast != NULL &&
		(check_right_node(ast, 1) || ast->type == COMMAND)))
		return (1);
	return (0);
}
