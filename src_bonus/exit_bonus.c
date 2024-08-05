/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:19:58 by likong            #+#    #+#             */
/*   Updated: 2024/08/05 17:07:21 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	success_exit(t_pipex *data)
{
	free_close(data);
	exit(SUCCESS);
}

void	close_pipe(t_pipex *data)
{
	int	i;
	// int	*fd;
	
	if (!data->fd)
		return ;
	i = 0;
	while(i < data->ac - 3 - data->here_doc)
	{
		if (data->fd[i * 2] >= 0)
			close(data->fd[i * 2]);
		if (data->fd[(i * 2) + 1] >= 0)
			close(data->fd[i * 2 + 1]);
		i++;
	}
	free(data->fd);
	data->fd = NULL;
}

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
	else if (error == HERE_DOC)
		ft_putstr_fd("Could not open here_doc file", STDERR);
	else if (error == NEXT_LINE)
		ft_putstr_fd("warning: here_doc at line 50 delimited by \
		end-of-file", STDERR);
	ft_putchar_fd('\n', STDERR);
}

void	show_error(t_pipex *data, char *message, t_error error, int err_fd)
{
	show_message(message, error);
	free_close(data);
	exit(err_fd);
}
