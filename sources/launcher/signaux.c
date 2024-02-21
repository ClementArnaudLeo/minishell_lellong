/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:07:19 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/18 03:45:28 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt_process(int signal)
{
	(void)signal;
	g_minishell.error_status = 130;
	write(1, "\n", 1);
}

static void	redisplay_prompt(int signal)
{
	(void)signal;
	g_minishell.error_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	quit_process(int signal)
{
	(void)signal;
	g_minishell.error_status = 131;
	ft_printf("Quit (core dumped)\n");
}

void	define_signals2(void)
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}

void	define_signals(void)
{
	signal(SIGINT, redisplay_prompt);
	signal(SIGQUIT, SIG_IGN);
}
