/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:13:18 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/23 21:53:03 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define TMP_FILE	"/tmp/minihell_temporary_file"

static int	create_temporary_file(void)
{
	int	fd;

	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		err_msg("redirect", strerror(errno), 1);
	return (fd);
}

static	void	get_and_write_input(int tmp_fd, char *eof)
{
	char	*input;

	signal(SIGINT, stop_here_doc);
	while (true)
	{
		input = readline("> ");
		if (!input)
		{
			err_msg("warning",
				"here-document delimited by end-of-file", 0);
			close(tmp_fd);
			exit(0);
		}
		if (ft_strcmp(input, eof))
			ft_putendl_fd(input, tmp_fd);
		else
		{
			close(tmp_fd);
			free(input);
			break ;
		}
		free(input);
	}
	exit(0);
}

static void	clear_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_WRONLY | O_TRUNC, 0600);
	close(tmp_fd);
}

static void	make_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_RDONLY);
	unlink(TMP_FILE);
	dup2(tmp_fd, IN);
	close(tmp_fd);
}

void	here_doc_input(char *eof, int *save_fd)
{
	int		tmp_fd;
	int		save_fd_out;
	int		pid;
	int		status;

	tmp_fd = create_temporary_file();
	if (tmp_fd == -1)
		return ;
	save_fd_out = dup(OUT);
	dup2(save_fd[OUT], STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		get_and_write_input(tmp_fd, eof);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		clear_tmp_file_input();
		g_minishell.error_status = 130;
	}
	make_tmp_file_input();
	dup2(save_fd_out, STDOUT_FILENO);
	close(save_fd_out);
}
