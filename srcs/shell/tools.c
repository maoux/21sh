/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:02:44 by heynard           #+#    #+#             */
/*   Updated: 2017/11/14 18:02:45 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"

static char		*ft_strchr_spec(const char *s, int c)
{
	if (*s == (char)c)
		return ((char *)s);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s += 1;
		if (*s == (char)c)
			return ((char *)s);
	}
	return ((char *)s);
}

static void		ft_innersplit(char **tabl, int *pos, int j, char const *s)
{
	int			i;

	i = 0;
	tabl[j][i++] = s[*pos];
	(*pos) += 1;
	while (s[(*pos)] != '$' && s[(*pos)] != '\0')
		tabl[j][i++] = s[(*pos)++];
	if (s[(*pos)] == '$' && i == 1)
	{
		tabl[j][i++] = '$';
		(*pos)++;
	}
	tabl[j][i] = '\0';
}

static char		**ft_split(char const *s, char **tabl, int i, int j)
{
	int			pos;

	pos = 0;
	while (s[pos])
	{
		if (s[pos] == '$')
		{
			tabl[j] = ft_strnew(ft_strlen_spec(ft_strchr_spec(&(s[pos + 1]),
									'$'), '$') + 1);
			ft_innersplit(tabl, &pos, j, s);
		}
		else
		{
			tabl[j] = ft_strnew(ft_strlen_spec(ft_strchr_spec(&(s[pos + 1]),
									'$'), '$') + 1);
			i = 0;
			while (s[pos] != '$' && s[pos] != '\0')
				tabl[j][i++] = s[pos++];
			tabl[j][i] = '\0';
		}
		j++;
		tabl[j] = NULL;
	}
	return (tabl);
}

static int		ft_count_char(char const *s, char c)
{
	int			pos;
	int			i;

	i = 0;
	pos = 0;
	while (s[pos])
	{
		if (s[pos] == '$')
			i++;
		pos++;
	}
	return (i);
}

char			**ft_strsplit_sh(char const *s)
{
	char		**tabl;

	tabl = (char **)malloc(sizeof(char *) * ft_count_char(s, '$') + 10);
	if (tabl == NULL)
		return (NULL);
	tabl[0] = NULL;
	tabl = ft_split(s, tabl, 0, 0);
	return (tabl);
}
