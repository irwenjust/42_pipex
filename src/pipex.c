/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:33:59 by likong            #+#    #+#             */
/*   Updated: 2024/08/02 10:22:22 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	dup_fd(t_pipex *data, int read_fd, int write_fd)
{
	if (dup2(read_fd, STDIN) == -1)
		show_error(data, NULL, DUP2, FAILSTD);
	if (dup2(write_fd, STDOUT) == -1)
		show_error(data, NULL, DUP2, FAILSTD);
	close(read_fd);
	close(write_fd);
}

static void	handle_child(t_pipex *data, int i)
{
	if (i == 0)
	{
		data->infile = open_file(data, i);
		dup_fd(data, data->infile, data->fd[1]);
	}
	else
	{
		data->outfile = open_file(data, i);
		dup_fd(data, data->fd[0], data->outfile);
	}
	close_pipe(data);
	handle_command(data, data->av[i + 2]);
	success_exit(data);
}

int	pipex(t_pipex *data)
{
	int		i;
	int		status;
	pid_t	pid[2];

	i = -1;
	status = 0;
	while ((++i) < 2)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			show_error(data, NULL, FORK, FAILSTD);
		if (pid[i] == 0)
			handle_child(data, i);
	}
	close_pipe(data);
	i = -1;
	while ((++i) < 2)
		status = pid_wait(pid[i]);
	return (status);
}
