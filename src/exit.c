/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:55:44 by likong            #+#    #+#             */
/*   Updated: 2024/07/28 12:43:12 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	show_message(char *message, t_error error)
{
	ft_putstr_fd("pipex: ", STDERR);
	if (error == FORK)
		ft_putstr_fd("fork() error", STDERR);
	else if (error == ENVP)
		ft_putstr_fd("ENVP error", STDERR);
	else if (error == MALLOC)
		ft_putstr_fd("malloc() failed in ", STDERR);
	else if (error == PIPE)
		ft_putstr_fd("pipe() creation failed", STDERR);
	else if (error == PERMISSION)
		ft_putstr_fd("permissions denied: ", STDERR);
	else if (error == FILE_NAME)
		ft_putstr_fd("no such file or directory: ", STDERR);
	if (message)
		ft_putstr_fd(message, STDERR);
}

void	show_error(t_pipex *data, char *message, t_error error)
{
	(void)data;
	show_message(message, error);
	free_close(data);
	exit(FAILURE);
}

void	success_exit(t_pipex *data)
{
	free_close(data);
	exit(SUCCESS);
}
