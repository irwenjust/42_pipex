/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:06:38 by likong            #+#    #+#             */
/*   Updated: 2024/07/27 12:53:42 by likong           ###   ########.fr       */
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
	if (message)
		ft_putstr_fd(message, STDERR);
}

void	show_error(t_pipex *data, char *message, t_error error)
{
	(void)data;
	show_message(message, error);
	
	exit(EXIT_FAILURE);
}
