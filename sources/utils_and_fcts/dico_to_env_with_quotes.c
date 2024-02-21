/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico_to_env_with_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:31:26 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/18 03:45:28 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*sub_fct(t_sous_dico *pair)
{
	char	*entry;
	char	*temp;
	char	*aux;
	char	*value_with_quotes;

	if (pair->value[0])
	{
		temp = ft_strjoin(pair->key, "=");
		aux = ft_strjoin("\"", pair->value);
		value_with_quotes = ft_strjoin(aux, "\"");
		entry = ft_strjoin(temp, value_with_quotes);
		free(temp);
		free(aux);
		free(value_with_quotes);
	}
	else
		entry = ft_strdup(pair->key);
	return (entry);
}

char	**dico_to_env_with_quotes(t_dico *table)
{
	unsigned int	i;
	unsigned int	j;
	t_sous_dico			*current;
	t_sous_dico			*temp;
	char			**env;

	i = 0;
	j = 0;
	env = (char **)ft_calloc(sizeof (char *), table->count + 1);
	while (i < table->size && j < table->count)
	{
		current = table->sous_dico[i];
		while (current != NULL)
		{
			temp = current->next;
			env[j] = sub_fct(current);
			current = temp;
			j++;
		}
		i++;
	}
	return (env);
}
