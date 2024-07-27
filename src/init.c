/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:32:18 by likong            #+#    #+#             */
/*   Updated: 2024/07/27 16:01:40 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	init_pipe(t_pipex *data)
{
	int	i;
	int	fd[2];

	i = 0;
	if (pipe(fd) == -1)
		show_error(data, NULL, PIPE);
}

static void	init_path(t_pipex *data, char **envp)
{
	int		i;
	char	**res;

	i = 0;
	if (!envp)
		show_error(data, NULL, ENVP);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			res = ft_split(envp[i] + 5, ':');
			if (!res)
				show_error(data, "ft_split", MALLOC);
			data->path = res;
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
	init_path(data, envp);
}
