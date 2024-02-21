/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:19:31 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/18 03:45:28 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_checker(t_token *head, int *old_pipe_in)
{
	t_token	*current;

	current = head;
	while (current)
	{
		if (current->type == T_PIPE)
		{
			command_parser(head, current, old_pipe_in);
			head = current->next;
			pipe_checker(head, old_pipe_in);
			break ;
		}
		current = current->next;
	}
	if (!current)
		command_parser(head, current, old_pipe_in);
}

static void	set_first_input_fd(int *old_pipe_in)
{
	*old_pipe_in = 0;
}

static void	close_last_input_fd(int old_pipe_in)
{
	if (old_pipe_in != 0)
		close(old_pipe_in);
}

void	parse_then_execute(t_token *token_lst)
{
	int	old_pipe_in;

	if (!token_lst)
		return ;
	set_first_input_fd(&old_pipe_in);
	pipe_checker(token_lst, &old_pipe_in);
	close_last_input_fd(old_pipe_in);
}
