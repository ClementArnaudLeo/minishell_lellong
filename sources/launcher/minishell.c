/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:28:42 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/23 22:48:07 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

static void	save_history(char *input)
{
	if (input && *input)
		add_history(input);
}

static void	read_input(char **input, bool *booleen)
{
	char	*prompt;

	prompt = create_prompt(booleen);
	define_signals();
	*input = readline(prompt);
	free(prompt);
}

static void	letsgo(void)
{
	bool	booleen;
	char	*input;
	t_token	*token_lst;

	booleen = false;
	while (true)
	{
		token_lst = NULL;
		input = NULL;
		read_input(&input, &booleen);
		save_history(input);
		tokenizer(&input, &token_lst);
		parse_then_execute(token_lst);
		token_list_clear(&token_lst);
		if (input)
			free(input);
	}
}

int	main(int argc, char **argv)
{
	if (argc > 1 && argv)
		err_msg("Error", TOO_MANY_ARGS, 666);
	g_minishell.env = env_to_dico(__environ);
	g_minishell.local_vars = dico_create_table(50);
	g_minishell.error_status = 0;
	letsgo();
	return (0);
}
