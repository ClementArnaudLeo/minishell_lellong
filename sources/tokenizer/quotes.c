/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:11:12 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/20 17:00:45 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_a_match2(char *line, int i, int *match_index, char c)
{
	while (line[i++] != '\0')
	{
		if (line[i] == c)
		{
			*match_index = i;
			return (TRUE);
		}
	}
	return (FALSE);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (TRUE);
	return (FALSE);
}


bool	is_between_quotes(char *line, int i, int *match_index, char c)
{
	if (is_quote(c) && has_a_match2(line, i, match_index, c))
		return (TRUE);
	return (FALSE);
}

void	remove_quotes(char **value, char quote)
{
	char	*temp;

	temp = ft_strtrim(*value, &quote);
	free(*value);
	*value = temp;
}
