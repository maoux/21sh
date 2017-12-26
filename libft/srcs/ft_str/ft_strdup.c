/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 17:43:12 by heynard           #+#    #+#             */
/*   Updated: 2017/05/13 20:03:14 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strdup(const char *s1)
{
	int		i;
	char	*result;

	i = 0;
	result = (char *)malloc(ft_strlen(s1) + 1);
	if (result)
	{
		while (s1[i] != '\0')
		{
			result[i] = s1[i];
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}
