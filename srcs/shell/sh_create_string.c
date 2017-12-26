/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_create_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 16:17:13 by heynard           #+#    #+#             */
/*   Updated: 2017/09/06 16:17:14 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

char			*sh_create_string(t_line *line)
{
	char		*str;
	t_string	*tmp;
	int			i;

	if (line->lsize < 2)
		return (NULL);
	if ((str = (char *)malloc(sizeof(char) * line->lsize)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "21sh: memory allocation failed\n");
		return (NULL);
	}
	tmp = line->string;
	i = 0;
	while (tmp->next)
	{
		str[i] = tmp->value;
		tmp = tmp->next;
		i++;
	}
	str[i] = '\0';
	return (str);
}
