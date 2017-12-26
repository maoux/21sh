/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 20:28:14 by heynard           #+#    #+#             */
/*   Updated: 2017/11/28 20:28:15 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static int			error_parsing(t_ast *ast, t_token *tmp, int error)
{
	if (error == 0)
		ft_dprintf(STDERR_FILENO, "21sh: parse error near '%s'\n", tmp->str);
	if (ast)
		sh_free_ast(ast);
	return (0);
}

char				**create_argv_tab(t_token *first, size_t size, t_token *tmp)
{
	char			**argv;

	while (tmp && !is_binary_operator(tmp->type))
	{
		size++;
		tmp = tmp->next;
	}
	if (!(argv = (char **)malloc(sizeof(char *) * size + 1)))
		return (NULL);
	tmp = first;
	argv = fill_null_tab(argv, size);
	size = 0;
	while (tmp && !is_binary_operator(tmp->type) && tmp->type != SEMI)
	{
		if (is_redirection_operator(tmp->type))
			tmp = tmp->next->next;
		else
		{
			argv[size++] = ft_strdup(tmp->str);
			tmp = tmp->next;
		}
	}
	return (argv);
}

void				free_argv_tab(char **argv)
{
	int				i;

	i = 0;
	if (argv)
	{
		while (argv[i] != NULL)
		{
			ft_strdel(&(argv[i]));
			i++;
		}
		free(argv);
	}
}

void				sh_end_parsing(t_shell *shell, t_ast *ast)
{
	if (ast && is_binary_operator(ast->type) && ast->right == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: parse error near '\\n'\n");
		sh_free_ast(ast);
		ast = NULL;
	}
	if (ast)
	{
		shell->err_closed = 0;
		if (!shell->simple_mode)
			sh_run_save_config(shell);
		sh_exec_tree(shell, ast);
		if (!shell->simple_mode)
			sh_run_term_config(shell);
		sh_free_ast(ast);
	}
}

int					sh_parse_lst(t_shell *shell, t_token *list, t_ast *ast)
{
	t_token			*tmp;
	int				error;

	tmp = list;
	while (tmp && tmp->type == SEMI)
		tmp = tmp->next;
	while (tmp)
	{
		error = 0;
		if (tmp->type == WORD || is_redirection_operator(tmp->type))
			ast = sh_parser_words(ast, &tmp, &error);
		else if (sh_condition_operator(ast, tmp) == 1)
			ast = sh_parser_operator(ast, &tmp);
		else if (tmp->type == SEMI)
			ast = sh_parser_semi(ast, &tmp);
		else
			return (error_parsing(ast, tmp, error));
		if (error == 1 || ast == NULL)
			return (error_parsing(ast, tmp, error));
	}
	sh_end_parsing(shell, ast);
	return (0);
}
