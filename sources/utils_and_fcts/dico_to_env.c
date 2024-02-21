/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico_to_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:44:33 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/18 03:45:28 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*sub_fct(t_sous_dico *pair)
{
	char	*entry;
	char	*temp;

	temp = ft_strjoin(pair->key, "=");
	entry = ft_strjoin(temp, pair->value);
	free(temp);
	return (entry);
}

char	**dico_to_env(t_dico *table)
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
