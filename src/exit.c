/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:44 by likong            #+#    #+#             */
/*   Updated: 2024/08/02 10:23:34 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	show_message(char *message, t_error error)
{
	ft_putstr_fd("pipex: ", STDERR);
	if (message)
		ft_putstr_fd(message, STDERR);
	if (error == FORK)
		ft_putstr_fd("fork() error", STDERR);
	else if (error == MALLOC)
		ft_putstr_fd(": malloc() failed", STDERR);
	else if (error == PIPE)
		ft_putstr_fd("pipe() creation failed", STDERR);
	else if (error == PERMISSION)
		ft_putstr_fd(": Permission denied", STDERR);
	else if (error == FILE_NAME)
		ft_putstr_fd(": No such file or directory", STDERR);
	else if (error == DUP2)
		ft_putstr_fd("dup2() error", STDERR);
	else if (error == DIRECTORY)
		ft_putstr_fd(": Is a directory", STDERR);
	else if (error == COMMAND)
		ft_putstr_fd(": command not found", STDERR);
	ft_putchar_fd('\n', STDERR);
}

void	show_error(t_pipex *data, char *message, t_error error, int err_fd)
{
	show_message(message, error);
	free_close(data);
	exit(err_fd);
}

void	success_exit(t_pipex *data)
{
	free_close(data);
	exit(SUCCESS);
}

void	close_pipe(t_pipex *data)
{
	if (!data->fd)
		return ;
	if (data->fd[0] >= 0)
		close(data->fd[0]);
	if (data->fd[1] >= 0)
		close(data->fd[1]);
	free(data->fd);
	data->fd = NULL;
}
