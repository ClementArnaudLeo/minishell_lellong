/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 23:57:34 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/23 22:48:39 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub_fct2(t_dico *table,
			t_sous_dico *current, char *key)
{
	t_sous_dico	*temp;

	while (current->next != NULL)
	{
		if (ft_strncmp(current->next->key, key, ft_strlen(key) + 1) == 0)
		{
			temp = current->next;
			current->next = current->next->next;
			dico_free_pair(temp);
			table->count -= 1;
			return ;
		}
		current = current->next;
	}
}

static void	sub3(t_dico *table, t_sous_dico *current,
			unsigned long int index)
{
	table->sous_dico[index] = current->next;
	dico_free_pair(current);
	table->count -= 1;
}

static void	sub4(t_dico *table, t_sous_dico *current,
			unsigned long int index)
{
	dico_free_pair(current);
	table->sous_dico[index] = NULL;
	table->count -= 1;
}

void	dico_delete(t_dico *table, char *key)
{
	unsigned long int	index;
	t_sous_dico				*current;

	index = hash(key, table->size);
	current = table->sous_dico[index];
	if (current == NULL)
		return ;
	else if (current->next == NULL
		&& ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
	{
		sub4(table, current, index);
		return ;
	}
	else if (current->next != NULL
		&& ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
	{
		sub3(table, current, index);
		return ;
	}
	else
		sub_fct2(table, current, key);
}
