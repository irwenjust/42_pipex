/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:33:59 by likong            #+#    #+#             */
/*   Updated: 2024/07/30 15:06:48 by likong           ###   ########.fr       */
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
	
	// ft_printf("infile: %d, outfile: %d\n", data->infile, data->outfile);
	if (i == 0)
	{
		// ft_printf("here?\n");
		data->infile = open_file(data, i);
		dup_fd(data, data->infile, data->fd[1]);
	}
	else
	{
		// ft_printf("also here?\n");
		data->outfile = open_file(data, i);
		dup_fd(data, data->fd[0], data->outfile);
	}
	close_pipe(data);
	handle_command(data, data->av[i + 2]);
	success_exit(data);
}

int	pipex(t_pipex *data)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while ((++i) < 2)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			show_error(data, NULL, FORK);
		if (data->pid[i] == 0)
		{
			// ft_printf("fd[0]: %d, fd[1]: %d\n", data->fd[0], data->fd[1]);
			handle_child(data, i);
		}
	}
	close_pipe(data);
	i = -1;
	while ((++i) < 2)
		status = pid_wait(data->pid[i]);
	return (status);
}
