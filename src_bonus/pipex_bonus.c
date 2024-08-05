/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:54:33 by likong            #+#    #+#             */
/*   Updated: 2024/08/05 14:40:14 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	dup_fd(t_pipex *data, int read_fd, int write_fd)
{
	if (dup2(read_fd, STDIN) == -1)
		show_error(data, NULL, DUP2, FAILSTD);
	if (dup2(write_fd, STDOUT) == -1)
		show_error(data, NULL, DUP2, FAILSTD);
	close(read_fd);
	close(write_fd);
}

//doubts here with fd position
static void	handle_child(t_pipex *data, int i)
{
	if (i == 0)
	{
		data->infile = open_file(data, i);
		dup_fd(data, data->infile, data->fd[1]);
	}
	else if (i == data->ac - 3 - data->here_doc - 1)
	{
		data->outfile = open_file(data, i);
		dup_fd(data, data->fd[(i - 1) * 2], data->outfile);
	}
	else
		dup_fd(data, data->fd[(i - 1) * 2], data->fd[i * 2 + 1]);
	close_pipe(data);
	handle_command(data, data->av[i + 2 + data->here_doc]);
	success_exit(data);
}

int	pipex(t_pipex *data)
{
	int		i;
	int		status;

	i = -1;
	status = 0;
	while ((++i) < data->ac - 3 - data->here_doc)
	{
		//ft_printf("Here: %d\n", data->here_doc);
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			show_error(data, NULL, FORK, FAILSTD);
		else if (data->pid[i] == 0)
			handle_child(data, i);
	}
	close_pipe(data);
	i = -1;
	while ((++i) < data->ac - 3 - data->here_doc)
		status = pid_wait(data->pid[i]);
	return (status);
}
