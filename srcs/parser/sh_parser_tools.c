/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 20:28:14 by heynard           #+#    #+#             */
/*   Updated: 2017/11/28 20:28:15 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

int					is_binary_operator(t_tokentype type)
{
	if (type == PIPE || type == AND_IF || type == OR_IF)
		return (1);
	return (0);
}

int					is_redirection_operator(t_tokentype type)
{
	if (type == GREAT || type == DGREAT || type == LESS || type == GREATAND ||
		type == GREATPIPE || type == DLESS)
		return (1);
	return (0);
}

int					is_right_required_operator(t_tokentype type)
{
	if (type == GREAT || type == DGREAT || type == LESS ||
		type == DLESS || type == GREATAND ||
		type == OR_IF || type == AND_IF || type == PIPE)
		return (1);
	return (0);
}

char				**fill_null_tab(char **argv, size_t size)
{
	size_t			i;

	i = 0;
	while (i <= size)
	{
		argv[i] = NULL;
		i++;
	}
	return (argv);
}

void				sh_free_ast(t_ast *ast)
{
	if (ast)
	{
		if (ast->right)
			sh_free_ast(ast->right);
		if (ast->left)
			sh_free_ast(ast->left);
		if (ast->type == COMMAND)
			free_argv_tab(ast->av);
		if (ast->redirection)
			free_redirection_list(ast->redirection);
		free(ast);
	}
}
