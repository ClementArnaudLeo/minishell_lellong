/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:53:17 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/21 17:35:51 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *value)
{
	if (!value)
		return (FALSE);
	if (!(ft_strcmp(value, "echo\0")) || !(ft_strcmp(value, "cd\0")))
		return (TRUE);
	if (!(ft_strcmp(value, "pwd")) || !(ft_strcmp(value, "export_")))
		return (TRUE);
	if (!(ft_strcmp(value, "unset")) || !(ft_strcmp(value, "env")))
		return (TRUE);
	if (!(ft_strcmp(value, "exit")))
		return (TRUE);
	return (FALSE);
}

bool	is_redirect(char *value)
{
	if (!ft_strcmp(value, ">") || !ft_strcmp(value, "<"))
		return (TRUE);
	if (!ft_strcmp(value, ">>"))
		return (TRUE);
	return (FALSE);
}

static bool	is_operator(char *value)
{
	if (!(ft_strcmp(value, "|")))
		return (TRUE);
	if (!(ft_strcmp(value, ">")) || !(ft_strcmp(value, "<")))
		return (TRUE);
	if (!(ft_strcmp(value, ">>")) || !(ft_strcmp(value, "<<")))
		return (TRUE);
	return (FALSE);
}

static int	define_operator(char *value)
{
	if (!(ft_strcmp(value, "|")))
		return (T_PIPE);
	if (is_redirect(value))
		return (T_REDIRECT);
	if (!(ft_strcmp(value, "<<")))
		return (T_REDIRECT);
	return (FALSE);
}

//defini le type du token parmis :
//BUILTIN LITERAL PIPE REDIRECT HERE_DOC FILE 
void	define_type(t_token *previous, char *value, int *type)
{
	int	previous_type;

	previous_type = 0;
	if (previous)
		previous_type = previous->type;
	if (is_builtin(value) && (previous_type != T_REDIRECT))
		*type = T_BUILTIN;
	else if (is_operator(value))
		*type = define_operator(value);
	else if (previous_type == T_REDIRECT)
		*type = T_FILE;
	else
		*type = T_LITERAL;
}
