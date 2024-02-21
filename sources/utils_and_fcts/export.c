/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:23:19 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/17 22:31:30 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_ordered_env(void)
{
	char	**ordered_env;

	ordered_env = dico_to_env_with_quotes(g_minishell.env);
	tri_array(ordered_env, 0, get_array_length(ordered_env));
	join_array("declare -x ", ordered_env);
	print_2d_array_fd(ordered_env, STDOUT_FILENO);
	free_2d_array(ordered_env);
	return (0);
}

static void	define_variable(char **cmd, int index)
{
	char	**variable;

	variable = split_by_two(cmd[index], '=');
	if (dico_search(g_minishell.env, variable[KEY]))
		dico_delete(g_minishell.env, variable[KEY]);
	dico_insert(variable[KEY], variable[VALUE], g_minishell.env);
	free_2d_array(variable);
}

static void	update_variable(char **cmd, int index)
{
	char	*value;
	bool	needtofree;

	needtofree = FALSE;
	if (dico_search(g_minishell.env, cmd[index]))
		return ;
	value = dico_search(g_minishell.local_vars, cmd[index]);
	if (!value)
	{
		value = ft_strdup("");
		needtofree = TRUE;
	}
	if (dico_search(g_minishell.env, cmd[index]))
		dico_delete(g_minishell.env, cmd[index]);
	dico_insert(cmd[index], value, g_minishell.env);
	dico_delete(g_minishell.local_vars, cmd[index]);
	if (needtofree)
		free(value);
}

static int	export_variable(char **cmd, int index)
{
	if (!cmd[index])
		return (0);
	if (ft_strchr(cmd[index], '='))
		define_variable(cmd, index);
	else
		update_variable(cmd, index);
	return (export_variable(cmd, index + 1));
}

int	export_(char **cmd)
{
	g_minishell.error_status = 0;
	if (cmd[1])
		return (export_variable(cmd, 1));
	else
		return (print_ordered_env());
}
