/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_insert_spaces.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:11:51 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/20 17:21:42 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//cherche c dans la str et fais pointer current à la pos de c
static bool	has_a_match(char **current, char c)
{
	char	*current_char;

	current_char = *current;
	current_char++;
	while (*current_char != '\0')
	{
		if (*current_char == c)
		{
			*current = current_char;
			return (TRUE);
		}
		current_char++;
	}
	return (FALSE);
}

//switch sur les operandes
static bool	is_operator(char *value)
{
	if (!(ft_strncmp(value, "|", 1)))
		return (TRUE);
	if (!(ft_strncmp(value, ">>", 2)) || !(ft_strncmp(value, "<<", 2)))
		return (TRUE);
	if (!(ft_strncmp(value, ">", 1)) || !(ft_strncmp(value, "<", 1)))
		return (TRUE);
	return (FALSE);
}

//self explanatory...
static bool	is_only_operator(char *current)
{
	char	quote;
	char	operator;

	quote = *current;
	current++;
	while (ft_isblank(*current))
		current++;
	if (!is_operator(current))
		return (FALSE);
	operator = *current;
	current++;
	if (*current == operator)
		current++;
	while (ft_isblank(*current))
		current++;
	if (*current != quote)
		return (FALSE);
	return (TRUE);
}

//check if the string is between "" ou ''
static bool	string_between_quotes(char **current)
{
	char	*current_char;

	current_char = *current;
	if (is_only_operator(current_char))
		return (FALSE);
	if (is_quote(*current_char) && has_a_match(current, *current_char))
		return (TRUE);
	return (FALSE);
}

//self explanatory...
void	check_and_insert_spaces(char **line)
{
	char	*current;
	char	*line_init;

	current = *line;
	line_init = *line;
	while (current && *current)
	{
		if (string_between_quotes(&current))
		{
			current++;
			continue ;
		}
		if (no_blanks_around_operator(current, line_init))
			current = insert_spaces(line, current, line_init);
		current++;
	}
}
