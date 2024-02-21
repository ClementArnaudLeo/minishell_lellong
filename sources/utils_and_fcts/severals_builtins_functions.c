/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   severals_builtins_functions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:43:47 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/03 09:34:20 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_working_directory(void)
{
	char	*buffer;

	buffer = NULL;
	return (getcwd(buffer, 0));
}

void	pwd(void)
{
	char	*cwd;

	g_minishell.error_status = 0;
	cwd = get_working_directory();
	if (cwd)
		ft_printf("%s\n", cwd);
	else
		err_msg("pwd", strerror(errno), 1);
	free(cwd);
}

void	print_environment(t_dico *env, int fd)
{
	char	**env_array;

	g_minishell.error_status = 0;
	env_array = dico_to_env(env);
	print_2d_array_fd(env_array, fd);
	free_2d_array(env_array);
}

void	unset(char **cmd)
{
	int	i;

	i = 1;
	g_minishell.error_status = 0;
	while (cmd[i])
	{
		if (dico_search(g_minishell.env, cmd[i]))
			dico_delete(g_minishell.env, cmd[i]);
		else if (dico_search(g_minishell.local_vars, cmd[i]))
			dico_delete(g_minishell.local_vars, cmd[i]);
		i++;
	}
}

void	echo(char **cmd)
{
	bool	n_flag;
	int		i;

	i = 1;
	n_flag = false;
	if (cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
	{
		n_flag = true;
		i = 2;
	}
	while (cmd && cmd[i])
	{
		ft_printf("%s ", cmd[i]);
		i++;
	}
	if (n_flag == false)
		ft_printf("\n");
	g_minishell.error_status = 0;
}
