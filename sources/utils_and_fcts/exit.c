/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:29:00 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/23 22:48:07 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_string_number(char *string)
{
	while (*string)
		if (!ft_isdigit(*string++))
			return (FALSE);
	return (TRUE);
}

static void	parse_first_arg(char *arg)
{
	if (!arg)
		return ;
	g_minishell.error_status = ft_atoi(arg);
	if (is_string_number(arg))
		return ;
	err_msg("exit", NEED_NUM_ARG, 2);
	exit_minishell();
}

static int	get_argc(char **argv)
{
	int	argc;

	argc = 0;
	while (*(++argv))
		argc++;
	return (argc);
}

void	exit_builtin(char **argv)
{
	int	argc;

	argc = get_argc(argv);
	parse_first_arg(*(argv + 1));
	if (argc > 1)
	{
		err_msg("exit", TOO_MANY_ARGS, 1);
		return ;
	}
	ft_printf("exit\n");
	exit_minishell();
}

void	exit_minishell(void)
{
	dico_free_table(g_minishell.env);
	dico_free_table(g_minishell.local_vars);
	exit(g_minishell.error_status);
}
