/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:11:49 by heynard           #+#    #+#             */
/*   Updated: 2017/07/11 14:11:51 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"
#include "../../libft/includes/libft.h"

static void		sh_print_current_time(void)
{
	char		*date;
	time_t		current_time;

	date = NULL;
	current_time = time(&current_time);
	date = ctime(&current_time);
	if (date)
	{
		date[16] = '\0';
		ft_dprintf(STDOUT_FILENO, " %s ", &(date[11]));
	}
}

static char		*sh_get_current_dir(t_shell *shell, char *current)
{
	int			i;
	char		*home;

	if (!ft_strcmp(current, " "))
		return (current);
	home = sh_get_var_env(shell->env, "HOME");
	if (home)
	{
		while (home[i] == current[i] && home[i] != '\0' && current[i] != '\0')
			i++;
		if (home[i] == '\0' && current[i] != '\0')
			return (&current[i] - ft_strlen(home) + 6);
	}
	return (current);
}

static void		print_prompt(t_shell *shell, char *current)
{
	ft_dprintf(STDOUT_FILENO, "%s[%s (%d) %s",
			GREEN, CLEAR,
			shell->nbl,
			BROWN);
	sh_print_current_time();
	ft_dprintf(STDOUT_FILENO, "%s %s]%s %s%s%s $~ ",
				CLEAR,
				GREEN, CLEAR,
				CYAN, current, CLEAR);
}

int				sh_prompt(t_shell *shell)
{
	char		*buffer;
	char		*tmp;

	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if (buffer == NULL)
	{
		sh_print_error(0, "21sh: cannot find current directory");
		buffer = ft_strdup(" ");
	}
	tmp = buffer;
	buffer = sh_get_current_dir(shell, buffer);
	shell->prompt_size = ft_strlen(buffer) + ft_count_digits(shell->nbl) + 19;
	print_prompt(shell, buffer);
	ft_strdel(&tmp);
	return (0);
}
