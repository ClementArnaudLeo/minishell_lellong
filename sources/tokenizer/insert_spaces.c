/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:11:19 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/20 17:06:51 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//taille de l'operateur (1 ou 2)
static int	get_operator_size(char *operator_pointer)
{
	if (*operator_pointer == *(operator_pointer + 1))
		return (2);
	return (1);
}

//frees
static void	free_aux_strings(char **left, char **operator, char **right)
{
	free(*left);
	free(*operator);
	free(*right);
}

//creates a new line by inserting spaces around the operator
static char	*create_new_line(char *line, char *operator_pointer,
		int operator_size, int off_set)
{
	char	*left;
	char	*operator;
	char	*right;
	char	*new_line;

	left = ft_substr(line, 0, off_set);
	operator = ft_substr(operator_pointer, 0, operator_size);
	right = ft_strdup(operator_pointer + operator_size);
	new_line = join_several_things(5, left, " ", operator, " ", right);
	free_aux_strings(&left, &operator, &right);
	return (new_line);
}

//insere des espaces autour des operateurs
char	*insert_spaces(char **line, char *operator_pointer, char *line_init)
{
	char	*new_line;
	int		operator_size;
	int		off_set;

	if (operator_pointer != line_init)
		if (*(operator_pointer - 1) == '>' || *(operator_pointer - 1) == '<')
			return (operator_pointer++);
	operator_size = get_operator_size(operator_pointer);
	off_set = operator_pointer - *line;
	new_line = create_new_line(*line, operator_pointer, operator_size, off_set);
	free(*line);
	*line = new_line;
	return (new_line + off_set + operator_size + 1);
}
