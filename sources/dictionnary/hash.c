/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:59:44 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/18 08:29:37 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//random hash algo souviens plus du nom ( nom dans l histo chatgpt )
unsigned long int	hash(char *key, unsigned int size)
{
	unsigned long int	hash;
	unsigned int		i;

	hash = 5381;
	i = 0;
	while (key && key[i])
	{
		hash = ((hash << 5) + hash) + key[i];
		i++;
	}
	return (hash % size);
}

t_sous_dico	*dico_create_pair(char *key, char *value)
{
	t_sous_dico	*new_pair;

	new_pair = (t_sous_dico *)ft_calloc(sizeof(t_sous_dico), 1);
	new_pair->key = ft_strdup(key);
	new_pair->value = ft_strdup(value);
	return (new_pair);
}

void	dico_free_pair(t_sous_dico *pair)
{
	free(pair->key);
	free(pair->value);
	free(pair);
}

static void	sub_fct(t_dico *table,
		unsigned long int index, t_sous_dico *new_pair)
{
	t_sous_dico	*current;

	current = table->sous_dico[index];
	while (current->next != NULL)
		current = current->next;
	current->next = new_pair;
	current->next->next = NULL;
	table->count += 1;
}

void	dico_insert(char *key, char *value, t_dico *table)
{
	unsigned long int	index;
	t_sous_dico				*new_pair;
	t_sous_dico				*current;

	index = hash(key, table->size);
	new_pair = dico_create_pair(key, value);
	current = table->sous_dico[index];
	if (current == NULL)
	{
		table->sous_dico[index] = new_pair;
		table->count += 1;
	}
	else
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			dico_free_pair(new_pair);
		}
		else
			sub_fct(table, index, new_pair);
	}
}
