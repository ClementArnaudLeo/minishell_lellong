/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:43:12 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/16 12:04:20 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_tild(char **new_value)
{
	*new_value = ft_strdup(dico_search(g_minishell.env, "HOME"));
	if (!*new_value)
		*new_value = ft_strdup("/");
}

static bool	is_only_dollar_sign(char *value)
{
	while (*value)
	{
		if (*value != '$')
			return (FALSE);
		value++;
	}
	return (TRUE);
}

static void	deal_with_multiple_dollar_sign(char **new_value, char *value)
{
	char	*total;

	total = ft_itoa(ft_strlen(value) / 2);
	*new_value = join_several_things(3, GREEN,
			total, //la je sui sas sur
			RESET_COLOR);
	free(total);
}

bool	if_is_special_case(char *value)
{
	if (!ft_strncmp(value, "~", 2))
		return (TRUE);
	else if (!ft_strncmp(value, "$", 2))
		return (TRUE);
	else if (!ft_strncmp(value, "$$", 3))
		return (TRUE);
	else if (is_only_dollar_sign(value))
		return (TRUE);
	return (FALSE);
}

void	cas_speciaux(char **value)
{
	char	*new_value;

	new_value = NULL;
	if (!ft_strncmp(*value, "~", 2))
		replace_tild(&new_value);
	else if (!ft_strncmp(*value, "$", 2))
		new_value = ft_strdup("$");
	else if (!ft_strncmp(*value, "$$", 3))
		new_value = join_several_things(3, GREEN,
				"invalid command", //remplacer par le PID du prgrm (je crois)
				RESET_COLOR);
	else if (is_only_dollar_sign(*value))
		deal_with_multiple_dollar_sign(&new_value, *value);
	free(*value);
	*value = new_value;
}
