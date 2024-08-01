/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:32:18 by likong            #+#    #+#             */
/*   Updated: 2024/08/01 18:36:23 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//doubts here
static void init_pipe(t_pipex *data)
{
	int	i;
	int	*fd;

	i = 0;
	fd = (int *)malloc(2 * sizeof(int));
	if (!fd)
		show_error(data, "init_pipe()", MALLOC, FAILSTD);
	if (pipe(fd) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		free(fd);
		show_error(data, NULL, PIPE, FAILSTD);
	}
	data->fd = fd;
}

static void	init_path(t_pipex *data, char **envp)
{
	int		i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			data->path = ft_split(envp[i] + 5, ':');
			if (!data->path)
				show_error(data, "ft_split()", MALLOC, FAILSTD);
			return ;
		}
		i++;
	}
}

void	init_data(t_pipex *data, int argc, char **argv, char **envp)
{
	data->ac = argc;
	data->av = argv;
	data->ep = envp;
	data->infile = -1;
	data->outfile = -1;
	data->path = NULL;
	data->fd = NULL;
	init_path(data, envp);
	init_pipe(data);
}
