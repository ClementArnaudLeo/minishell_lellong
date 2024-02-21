/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:09:17 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/01 18:53:28 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stop_here_doc(int signal)
{
	(void)signal;
	g_minishell.error_status = 130;
	write(1, "\n", 1);
	exit(130);
}

void	err_msg(char *input, char *err_msg, int status)
{
	char	*error_output;

	error_output = join_several_things(
	7,BOLD_YELLOW,"minishell: ",YELLOW, 
	input, ": ", err_msg, RESET_COLOR);
	ft_putendl_fd(error_output, 2);
	g_minishell.error_status = status;
	free(error_output);
}
