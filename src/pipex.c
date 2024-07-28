/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:33:59 by likong            #+#    #+#             */
/*   Updated: 2024/07/28 12:42:33 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	dup_fd(t_pipex *data, int read_fd, int write_fd)
{
	if (dup2(read_fd, STDIN) == -1)
		show_error(data, NULL, DUP2);
	if (dup2(write_fd, STDOUT) == -1)
		show_error(data, NULL, DUP2);
	close(read_fd);
	close(write_fd);
}

static void	handle_child(t_pipex *data, int i)
{
	open_file(data, i);
	if (i == 0)
		dup_fd(data, data->infile, data->fd[1]);
	else
		dup_fd(data, data->fd[0], data->outfile);
	close(data->fd[0]);
	close(data->fd[1]);
	handle_command(data, data->av[i + 2]);
	success_exit(data);
}

void	pipex(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			show_error(data, NULL, FORK);
		if (data->pid[i] == 0)
			handle_child(data, i);
		i++;
	}
}
