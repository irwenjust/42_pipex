/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:08:12 by likong            #+#    #+#             */
/*   Updated: 2024/07/28 16:30:36 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*check_slash(char *cmd)
{
	if (*cmd != '/')
		return (NULL);
	return (cmd);
}

int	check_empty(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (check_white(str[i]))
			return (1);
	return (0);
}

//Doubts here
void	free_close(t_pipex *data)
{
	if (data->infile >= 0)
		close(data->infile);
	if (data->outfile >= 0)
		close(data->outfile);
	free_matrix(data->path);
}

void	open_file(t_pipex *data, int i)
{
	int		fd;
	char	*file_name;

	if (i == 0)
	{
		file_name = data->av[1];
		if (access(file_name, F_OK) && access(file_name, R_OK) == -1)
			show_error(data, file_name, PERMISSION);
		fd  = open(file_name, O_RDONLY, 0444);
	}
	else
	{
		file_name = data->av[4];
		if (access(file_name, F_OK) && access(file_name, W_OK) == -1)
			show_error(data, file_name, PERMISSION);
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd == -1)
		show_error(data, file_name, FILE_NAME);
	data->infile = fd;
}
