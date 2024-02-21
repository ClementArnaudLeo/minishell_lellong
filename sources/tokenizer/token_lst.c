/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:56:24 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/18 03:45:28 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *value, int type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	new_token->previous = NULL;
	return (new_token);
}

t_token	*token_last(t_token *lst)
{
	t_token	*aux;

	if (lst == NULL)
		return (lst);
	aux = lst;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	token_add_back(t_token **lst, t_token *new_token)
{
	t_token	*aux;

	if (new_token == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_token;
		return ;
	}
	aux = token_last(*lst);
	aux->next = new_token;
	new_token->previous = aux;
}

void	token_list_clear(t_token **lst)
{
	t_token	*aux;
	t_token	*temp;

	aux = *lst;
	if (aux == NULL)
		return ;
	while (aux != NULL)
	{
		temp = aux->next;
		free(aux->value);
		free(aux);
		aux = temp;
	}
	*lst = NULL;
}
