/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_window_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:39:40 by heynard           #+#    #+#             */
/*   Updated: 2017/07/31 14:39:41 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell21.h"
#include "../../libft/includes/libft.h"

static int		sh_inner_setup_terminal(t_shell *shell)
{
	if (!(shell->win_size = (struct winsize *)malloc(sizeof(struct winsize))))
		return (1);
	if (ioctl(0, TIOCGWINSZ, shell->win_size) < 0)
		return (1);
	if (!(shell->save_term = (struct termios *)malloc(sizeof(struct termios))))
		return (1);
	if (!(shell->current_term =
			(struct termios *)malloc(sizeof(struct termios))))
		return (1);
	if (tcgetattr(0, shell->save_term) < 0)
		return (1);
	tcgetattr(0, shell->current_term);
	shell->current_term->c_lflag &= ~(ICANON);
	shell->current_term->c_lflag &= ~(ECHO);
	shell->current_term->c_cc[VMIN] = 1;
	shell->current_term->c_cc[VTIME] = 100;
	return (0);
}

int				ft_putcharint(int c)
{
	write(1, &c, 1);
	return (0);
}

int				sh_setup_terminal(t_shell *shell)
{
	char		*term_name;

	if ((term_name = getenv("TERM")) == NULL)
	{
		sh_print_error(0, "21sh: TERM variable not found");
		shell->simple_mode = TRUE;
		return (1);
	}
	if (tgetent(NULL, term_name) <= 0)
	{
		sh_print_error(0, "21sh: cannot find terminal configuration");
		shell->simple_mode = TRUE;
		return (1);
	}
	if (sh_inner_setup_terminal(shell))
	{
		sh_print_error(0, "21sh: cannot setup terminal configuration");
		shell->simple_mode = TRUE;
		return (1);
	}
	return (0);
}

void			sh_run_term_config(t_shell *shell)
{
	tcsetattr(0, TCSADRAIN, shell->current_term);
	tputs(tgetstr("vi", NULL), 1, ft_putcharint);
}

void			sh_run_save_config(t_shell *shell)
{
	tcsetattr(0, TCSADRAIN, shell->save_term);
	tputs(tgetstr("ve", NULL), 1, ft_putcharint);
}
