/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_blanks_around.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:55:55 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/20 17:09:09 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check si le char pointé est entre des espaces
static bool	is_between_blanks(char *line, char *init)
{
	if (line == init)
	{
		if (ft_isblank(*(line + 1)))
			return (TRUE);
		else
			return (FALSE);
	}
	if ((ft_isblank(*(line - 1))) && (ft_isblank(*(line + 1))))
		return (TRUE);
	return (FALSE);
}

//check si le char est suivi par le meme char
static bool	is_double(char *line)
{
	if (*(line + 1) == *line)
		return (TRUE);
	return (FALSE);
}

//self explenatory...
static bool	no_blanks_around_double(char *line, char *line_minus_one)
{
	if (!ft_isblank(*(line_minus_one)) || !ft_isblank(*(line + 2)))
		return (TRUE);
	return (FALSE);
}

//self explenatory...
static bool	no_blanks_around_redirect(char *line,
	char *line_minus_one, char *line_init)
{
	if (is_double(line) && no_blanks_around_double(line, line_minus_one))
		return (TRUE);
	else
		if (!(is_between_blanks(line, line_init)))
			return (TRUE);
	return (FALSE);
}

//main function that checks if there are no blanks around operators
bool	no_blanks_around_operator(char *line, char *line_init)
{
	char	*line_minus_one;

	line_minus_one = line - 1;
	if (line == line_init)
		line_minus_one = line;
	if ((*line == '|') && !(is_between_blanks(line, line_init)))
		return (TRUE);
	if (*line == '>' || *line == '<')
		if (no_blanks_around_redirect(line, line_minus_one, line_init))
			return (TRUE);
	return (FALSE);
}
