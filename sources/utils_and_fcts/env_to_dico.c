/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_dico.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:04:52 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/18 03:45:28 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*seek_value(char *env_line)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (env_line[i] != '=')
		i++;
	j = i;
	while (env_line[j])
		j++;
	value = ft_substr(env_line, i + 1, j);
	return (value);
}

static char	*seek_key(char *env_line)
{
	int		i;
	char	*key;

	i = 0;
	while (env_line[i] != '=')
		i++;
	key = ft_substr(env_line, 0, i);
	return (key);
}

t_dico	*env_to_dico(char **env)
{
	int			len;
	int			i;
	t_dico	*table;
	char		*key;
	char		*value;

	len = 0;
	i = 0;
	while (env[len])
		len++;
	table = dico_create_table(len * 2);
	while (i < len)
	{
		key = seek_key(env[i]);
		value = seek_value(env[i]);
		dico_insert(key, value, table);
		i++;
		free(key);
		free(value);
	}
	return (table);
}
