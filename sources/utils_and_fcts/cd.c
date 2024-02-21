/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:33:57 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/16 11:49:58 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//change le répertoire courant en se basant sur l'arg, et save le OLDPWD
static void	change_dir_to_arg(char *path)
{
	char	*pwd;
	char	*error_msg;
	char	buffer[2048];

	pwd = getcwd(buffer, 2048);
	dico_insert("OLDPWD", pwd, g_minishell.env);
	if (chdir(path) != 0 && ft_strchr(path, '>') == NULL)
	{
		error_msg = ft_strjoin("cd: ", path);
		err_msg(error_msg, strerror(errno), 1);
		free(error_msg);
		return ;
	}
	pwd = getcwd(buffer, 2048);
	dico_insert("PWD", pwd, g_minishell.env);
}

//change le répertoire courant en se basant sur la variable d'environnement OLDPWD
static void	change_dir_to_oldpwd(char *path)
{
	ft_printf("%s\n", path);
	change_dir_to_arg(path);
}

//facile
static void	change_dir_to_home(void)
{
	char	*path;

	path = ft_strdup(dico_search(g_minishell.env, "HOME"));
	if (path == NULL)
	{
		err_msg("cd", NO_HOME, 1);
		free(path);
		return ;
	}
	change_dir_to_arg(path);
	free(path);
}

//fct princiapl type 'switch' pour call la bonne sous-fct
void	cd(char	*path)
{
	char	*current_path;

	g_minishell.error_status = 0;
	if ((!path) || ft_strcmp(path, "~") == 0)
	{
		change_dir_to_home();
		return ;
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		current_path = ft_strdup(dico_search(g_minishell.env, "OLDPWD"));
		if (current_path == NULL)
		{
			err_msg("cd", NO_OLDPWD, 1);
			return ;
		}
		change_dir_to_oldpwd(current_path);
	}
	else
	{
		current_path = ft_strdup(path);
		change_dir_to_arg(current_path);
	}
	free(current_path);
}
