/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:48:28 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/23 22:49:02 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dico	*dico_create_table(unsigned int size)
{
	t_dico		*new_table;
	unsigned int	i;

	i = 0;
	new_table = (t_dico *)ft_calloc(sizeof(t_dico), 1);
	new_table->size = size;
	new_table->count = 0;
	new_table->sous_dico = (t_sous_dico **)ft_calloc(sizeof(t_dico), size);
	while (i < size)
	{
		new_table->sous_dico[i] = NULL;
		i++;
	}
	return (new_table);
}

char	*dico_search(t_dico *table, char *key)
{
	unsigned long int	index;
	t_sous_dico				*current;

	index = hash(key, table->size);
	current = table->sous_dico[index];
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	dico_free_table(t_dico *table)
{
	unsigned int	i;
	t_sous_dico			*current;
	t_sous_dico			*temp;

	i = 0;
	while (i < table->size)
	{
		current = table->sous_dico[i];
		while (current != NULL)
		{
			temp = current->next;
			dico_free_pair(current);
			current = temp;
		}
		i++;
	}
	free(table->sous_dico);
	free(table);
}
