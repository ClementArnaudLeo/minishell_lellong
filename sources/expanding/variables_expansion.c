/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:25:26 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/23 22:43:55 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	dollar_question(char **value)
{
	if (ft_strcmp(*value, "$?") == 0)
	{
		free(*value);
		*value = ft_itoa(g_minishell.error_status);
		return (TRUE);
	}
	return (FALSE);
}

static void	string_slices(t_var *var, char **value, int *i)
{
	var->before = ft_substr(*value, 0, *i);
	var->value = ft_substr(*value, *i, get_var_size(var->pointer, i));
	if (ft_strchr(var->value, '\''))
		handle_var_squote(var, value, *i);
	else
		var->after = ft_substr(*value, *i, (ft_strlen(*value) - *i));
	expand(&var->value);
}

static bool	has_dollar_sign(char **value, int *i, t_var *var)
{
	if (!(*value) || dollar_question(value))
		return (FALSE);
	var->pointer = search_var(*value, i);
	if (!(var->pointer))
		return (FALSE);
	return (TRUE);
}

static bool	only_dollar_sign_between_quotes(char **value)
{
	if (!ft_strcmp(*value, "\"$\""))
	{
		free(*value);
		*value = ft_strdup("$");
		return (TRUE);
	}
	return (FALSE);
}

void	expand_variables(char **value)
{
	t_var	var;
	char	*new_str;
	int		i;

	i = 0;
	if (!has_dollar_sign(value, &i, &var)
		|| only_dollar_sign_between_quotes(value))
		return ;
	string_slices(&var, value, &i);
	new_str = join_several_things(3, var.before, var.value, var.after);
	free(*value);
	*value = new_str;
	free_var_struct(&var);
	expand_variables(value);
}
