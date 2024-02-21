/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:41:45 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/23 22:43:55 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_some_stuffs(char **temp, char **aux, char **splited_str)
{
	ft_free_and_null((void **)temp);
	ft_free_and_null((void **)aux);
	free_2d_array(splited_str);
}

static void	join_single_quote(char **splited_string, char **temp)
{
	if (splited_string[1])
		*temp = ft_strjoin("\'", splited_string[1]);
	else
		*temp = ft_strdup("\'");
}

void	handle_var_squote(t_var *var, char **value, int i)
{
	char	**splited_string;
	char	*temp;
	char	*aux;

	splited_string = ft_split(var->value, SINGLE_QUOTE);
	ft_free_and_null((void **)&var->value);
	var->value = ft_strdup(splited_string[0]);
	join_single_quote(splited_string, &temp);
	aux = ft_substr(*value, i, (ft_strlen(*value) - i));
	var->after = ft_strjoin(temp, aux);
	free_some_stuffs(&temp, &aux, splited_string);
}
