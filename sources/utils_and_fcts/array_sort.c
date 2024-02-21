/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:20:30 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/03 09:28:55 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fct2(char **array, int left, int right)
{
	int		i;
	int		j;
	char	*pivot;
	char	*temp;

	pivot = array[left];
	i = left;
	j = left + 1;
	while (j <= right)
	{
		if (ft_strcmp(pivot, array[j]) > 0)
		{
			i++;
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
		j++;
	}
	temp = pivot;
	array[left] = array[i];
	array[i] = temp;
	return (i);
}

void	tri_array(char **array, int left, int right)
{
	int	pivot_index;

	if (left < right)
	{
		pivot_index = fct2(array, left, right);
		tri_array(array, left, pivot_index - 1);
		tri_array(array, pivot_index + 1, right);
	}
}
