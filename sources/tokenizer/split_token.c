/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:41:56 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/21 17:39:03 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_quotes(char **value)
{
	int		i;
	int		end_quote;
	char	*token;

	i = 0;
	token = *value;
	while (token[i])
	{
		if (is_between_quotes(token, i, &end_quote, token[i]))
		{
			handle_quotes(&token, i, &end_quote);
			i = end_quote - 1;
			if (i < 0)
				i = 0;
		}
		if (token[i])
			i++;
	}
	*value = token;
}

void	add_token(char *line, int start, int end, t_token **token_lst)
{
	char	*value;
	int		type;

	value = ft_substr(line, start, (end - start));
	if (!value)
		return ;
	if (if_is_special_case(value))
		cas_speciaux(&value);
	else if (ft_strchr(value, '\'') || ft_strchr(value, '\"'))
		check_quotes(&value);
	else if (ft_strchr(value, '$'))
		expand_variables(&value);
	define_type(token_last(*token_lst), value, &type);
	token_add_back(token_lst, token_new(value, type));
}

void	define_end_quote(char *token, bool has_variable,
			char first_quote, int *end_quote)
{
	char	*quote;

	quote = NULL;
	quote = ft_strchr(token, '\"');
	if (!quote && !has_variable)
		quote = ft_strchr(token, '\'');
	else if (quote && first_quote != '\'')
	{
		*quote = '\0';
		*end_quote = ft_strlen(token);
		*quote = '\"';
	}
	else if (!quote || first_quote == '\'')
		*end_quote = ft_strlen(token);
	else
	{
		*quote = '\0';
		*end_quote = ft_strlen(token);
		*quote = '\'';
	}
}

static int	find_end(char *line, int i, int *end)
{
	while (!(ft_isblank(line[i])) && (line[i]))
	{
		if (is_between_quotes(line, i, &i, line[i]))
		{
			i++;
			continue ;
		}
		i++;
	}
	*end = i;
	return (i);
}

//split la cmd en token (valeur +type) a chaque espace sauf strings 
int	split_token(char *line, int *i, int *tkn_end, t_token **token_lst)
{
	while (ft_isblank(line[*i]))
		*i += 1;
	if (!line[*i])
		return (0);
	add_token(line, *i, find_end(line, *i, tkn_end), token_lst);
	*i = *tkn_end;
	if (line[*i])
		*i += 1;
	return (1);
}
