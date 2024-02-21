/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:56:39 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/23 22:48:07 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_dquotes(char **temp, bool *has_quote, char **key)
{
	if (ft_strchr(*temp, '\"'))
	{
		*key = ft_strtrim(*temp, "\"");
		*has_quote = TRUE;
	}
	else
		*key = ft_strdup(*temp);
}

static void	define_value(char **value, char *key)
{
	*value = ft_strdup(dico_search(g_minishell.env, key));
	if (!*value)
		*value = ft_strdup(dico_search(g_minishell.local_vars, key));
	if (!*value)
		*value = ft_strdup("");
}

static void	put_quote_back(bool has_quote, char **value, char **temp)
{
	if (has_quote)
	{
		*temp = ft_strjoin(*value, "\"");
		free(*value);
		*value = ft_strdup(*temp);
		free(*temp);
	}
}

void	expand(char **variable)
{
	char	*value;
	char	*key;
	char	*temp;
	bool	has_quote;

	has_quote = FALSE;
	temp = *variable;
	temp++;
	check_dquotes(&temp, &has_quote, &key);
	define_value(&value, key);
	free(*variable);
	free(key);
	put_quote_back(has_quote, &value, &temp);
	*variable = value;
}
