/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:40:47 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/01 18:52:43 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pwd(void)
{
	char	*buffer;

	buffer = NULL;
	return (getcwd(buffer, 0));
}

static char	*joli_prompt(char *name, char *pwd, char *end)
{
	char	*prompt;

	prompt = join_several_things(6, CYAN, name, pwd,
	BOLD_RED, end, RESET_BOLD_RED);
	free(name);
	free(pwd);
	free(end);
	return (prompt);
}

//pourquoi j'ai fait ça ??? a quoi ça sert ?
static char	*create_name(bool *booleen)
{
	if (!*booleen)
	{
		*booleen = true;
		return (ft_strdup("\n"));
	}
	if (g_minishell.error_status == 0)
		return (ft_strdup(""));
	return (ft_strdup(""));
}

char	*create_prompt(bool *booleen)
{
	char	*name;
	char	*pwd;
	char	*end;

	pwd = get_pwd();
	name = create_name(booleen);
	end = ft_strdup("$ ");
	return (joli_prompt(name, pwd, end));
}
