/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:01:46 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/21 14:58:09 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_eof(char *line)
{
	if (line)
		return ;
	ft_printf("exit\n");
	exit_minishell();
}

static bool	is_single_dollar_sign(char *line)
{
	while (ft_isblank(*line))
		line++;
	if (!(*line))
		return (FALSE);
	if (*line == '$')
		line++;
	while (ft_isblank(*line))
		line++;
	if (*line)
		return (FALSE);
	err_msg("$", NOT_FOUND, 127);
	return (TRUE);
}

static bool	no_need_to_tokenization(char *line)
{
	check_eof(line);
	if (line[0] == '\0')
		return (TRUE);
	if (is_single_dollar_sign(line))
		return (TRUE);
	return (FALSE);
}

/*
check_and_insert_spaces : met les espaces entre les redirection, pipes et endroit ou ils
 sont aps obligatoires normalement ( pas dans les quotes)

split_token : split la cmd a chaque espace (sauf entre guillemets) et assigne pour chaque 'token'
la valeur et le type (utile + tard), s occupe aussi de l expansion
*/

void	tokenizer(char **line, t_token **token_lst)
{
	int		i;
	int		token_end;

	i = 0;
	if (no_need_to_tokenization(*line))
		return ;
	check_and_insert_spaces(line);
	token_end = i;
	while ((*line)[i])
		if (!split_token(*line, &i, &token_end, token_lst))
			break ;
}
