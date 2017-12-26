/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 13:41:59 by heynard           #+#    #+#             */
/*   Updated: 2017/07/31 13:42:00 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINEDITING_H
# define LINEDITING_H

# define KEY_UP				4283163
# define KEY_RIGHT			4414235
# define KEY_LEFT			4479771
# define KEY_DOWN			4348699
# define KEY_SPACE			32
# define KEY_ESC			27
# define KEY_DELETE			127
# define KEY_PAD_DEL		2117294875
# define KEY_PAD_HOME		4741915
# define KEY_PAD_END		4610843
# define KEY_CTRL_UP		30078481937729
# define KEY_CTRL_DOWN		30078481937730
# define KEY_CTRL_R			18
# define KEY_CTRL_A			1
# define KEY_CTRL_I			9
# define KEY_CTRL_L			12
# define KEY_CTRL_P			16
# define KEY_ARROW_LEFT		44
# define KEY_ARROW_RIGHT	46
# define KEY_TAB			9
# define KEY_SHIFT_TAB		5921563
# define KEY_SHIFT_UP		71683997260571
# define KEY_SHIFT_LEFT		74982532143899
# define KEY_SHIFT_RIGHT	73883020516123
# define KEY_SHIFT_DOWN		72783508888347
# define KEY_BRACKET_OPEN	40
# define KEY_BRACKET_CLOSE	41
# define KEY_COPY			42
# define KEY_CUT			45
# define KEY_PASTE			43
# define KEY_RETURN			10
# define KEY_CTRL_D			4
# define KEY_HOME			4741915
# define KEY_END			4610843

# define CLEAR				"\033[0m"
# define BOLD				"\033[1m"
# define UNDERLINE			"\033[4m"
# define BLACK				"\033[30m"
# define RED				"\033[31m"
# define GREEN				"\033[32m"
# define BROWN				"\033[33m"
# define BLUE				"\033[34m"
# define MAGENTA			"\033[35m"
# define CYAN				"\033[36m"
# define LIGHTGREY			"\033[37m"
# define BLACK2				"\033[2;30m"
# define RED2				"\033[2;31m"
# define GREEN2				"\033[2;32m"
# define BROWN2				"\033[2;33m"
# define BLUE2				"\033[2;34m"
# define MAGENTA2			"\033[2;35m"
# define CYAN2				"\033[2;36m"
# define LIGHTGREY2			"\033[2;37m"
# define BLACK3				"\033[1;30m"
# define RED3				"\033[1;31m"
# define GREEN3				"\033[1;32m"
# define BROWN3				"\033[1;33m"
# define BLUE3				"\033[1;34m"
# define MAGENTA3			"\033[1;35m"
# define CYAN3				"\033[1;36m"
# define LIGHTGREY3			"\033[1;37m"
# define BG_BLACK			"\033[7;30m"
# define BG_RED				"\033[7;31m"
# define BG_GREEN			"\033[7;32m"
# define BG_BROWN			"\033[7;33m"
# define BG_BLUE			"\033[7;34m"
# define BG_MAGENTA			"\033[7;35m"
# define BG_CYAN			"\033[7;36m"
# define BG_LIGHTGREY		"\033[7;37m"

# include <term.h>

/*
** linked list storing the current string input by user and
** some informations about each caracters.
*/

typedef struct				s_string
{
	char			value;
	short int		selected;
	short int		cursor;
	struct s_string	*prev;
	struct s_string	*next;
}							t_string;

/*
** double linked list to keep all the previous command input by the user
** during one session.
*/

typedef struct				s_histo
{
	struct s_string		*line;
	struct s_histo		*next;
	struct s_histo		*prev;
	short int			current;
	int					lsize;
}							t_histo;

/*
** struct storing informations about the current string
** the user is inputing, the cursor position on the current line
** and the sise of the current line.
*/

typedef struct				s_line
{
	struct s_string		*string;
	struct s_string		*copy;
	struct s_cursor		*cursor;
	int					lsize;
	int					selection;
}							t_line;

typedef struct				s_cursor
{
	int					x;
	int					y;
}							t_cursor;

int							ft_putcharint(int c);

#endif
