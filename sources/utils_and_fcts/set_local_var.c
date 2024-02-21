/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_local_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:40:01 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/16 11:56:03 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//facile
static void update_variable(t_dico *table, char *key, char *value)
{
	dico_delete(table, key);
	dico_insert(key, value, table);
}

//trouve la bonne struct ou se trouve la var
static t_dico *fond_correct_dico(char **variable)
{
	t_dico *table;

	if (dico_search(g_minishell.env, variable[KEY]))
		table = g_minishell.env;
	else if (dico_search(g_minishell.local_vars, variable[KEY]))
		table = g_minishell.local_vars;
	else
		table = NULL;
	return (table);
}

//decoupe la clé et la valeur, puis utilise les fct du haut pour insert la var
static void define_variable(char **cmd, int index)
{
	char **variable;
	t_dico *table;

	variable = split_by_two(cmd[index], '=');
	table = fond_correct_dico(variable);
	if (table)
		update_variable(table, variable[KEY], variable[VALUE]);
	else
		dico_insert(variable[KEY], variable[VALUE], g_minishell.local_vars);
	free_2d_array(variable);
}

//appel define_variable tant que il y'a encore des "=" ou la fin
static int set_variables(char **cmd, int *index)
{
	if ((!cmd[*index]) || (!(ft_strchr(cmd[*index], '='))))
		return (0);
	define_variable(cmd, *index);
	*index += 1;
	return (set_variables(cmd, index));
}

int set_local_var(char **cmd, int *i)
{
	set_variables(cmd, i);
	return (1);
}
