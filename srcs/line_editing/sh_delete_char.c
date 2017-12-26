/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_delete_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 16:36:47 by heynard           #+#    #+#             */
/*   Updated: 2017/12/15 16:36:48 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

t_string			*sh_delete_2char_in_string(t_string *str, t_string *tmp)
{
	t_string		*to_del;

	to_del = tmp;
	tmp = tmp->prev;
	tmp->prev->next = to_del->next;
	if (to_del->next)
		to_del->next->prev = tmp->prev;
	free(tmp);
	free(to_del);
	return (str);
}

t_string			*sh_delete_char_in_string(t_string *str)
{
	t_string		*ret;
	t_string		*tmp;

	if (str->next == NULL)
		return (str);
	tmp = str;
	while (tmp->cursor == 0)
		tmp = tmp->next;
	tmp = tmp->prev;
	if (tmp->value == '\n' && tmp->prev)
		return (sh_delete_2char_in_string(str, tmp));
	if (tmp->prev)
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	else
	{
		tmp->next->prev = tmp->prev;
		ret = tmp->next;
		free(tmp);
		return (ret);
	}
	free(tmp);
	return (str);
}
