/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:08:12 by likong            #+#    #+#             */
/*   Updated: 2024/07/30 18:54:58 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	pid_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (FAILURE);
}

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
	if (str[0] == '\0')
		return (1);
	while (str[++i])
		if (!check_white(str[i]))
			return (0);
	return (1);
}

//Doubts here
void	free_close(t_pipex *data)
{
	if (data->infile >= 0)
		close(data->infile);
	if (data->outfile >= 0)
		close(data->outfile);
	if (data->pid)
		free(data->pid);
	close_pipe(data);
	free_matrix(data->path);
}

int	open_file(t_pipex *data, int i)
{
	int		fd;
	char	*file_name;

	if (i == 0)
	{
		file_name = data->av[1];
		if (access(file_name, F_OK) == 0 && access(file_name, R_OK) == -1)
			show_error(data, file_name, PERMISSION);
		fd  = open(file_name, O_RDONLY, 0444);
	}
	else
	{
		file_name = data->av[4];
		//ft_printf("access: %d\n", access(file_name, F_OK));
		if (access(file_name, F_OK) == 0 && access(file_name, W_OK) == -1)
			show_error(data, file_name, PERMISSION);
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd == -1)
		show_error(data, file_name, FILE_NAME);
	return (fd);
}
