/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:56:53 by likong            #+#    #+#             */
/*   Updated: 2024/07/30 18:34:08 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	handle_cmd_error(int status, char *cmd, t_pipex *data)
{
	if (status == -1)
		show_error(data, cmd, PERMISSION);
	if (access(cmd, F_OK) == -1 && errno == ENOTDIR)
		show_error(data, cmd, DIRECTORY);
	//ft_printf("here\n");
	show_error(data, cmd, COMMAND);
}

static char	*combine_path(char *path1, char *path2)
{
	size_t	len_1;
	size_t	len_2;
	char	*res;
	
	if (*path1 == '\0')
		return (path2);
	len_1 = ft_strlen(path1);
	len_2 = ft_strlen(path2);
	res = (char *)malloc((len_1 + len_2 + 2) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, path1, len_1 + 1);
	ft_strlcpy(res + len_1, "/", 2);
	ft_strlcpy(res + len_1 + 1, path2, len_2 + 1);
	return (res);
}

// This function will execute the command
// The path is path from envp
// The cmd is command
// The abs_cmd is absolute path for command(with command itself)
// The cmds saves command(like wc -l)
static int	exec_cmd(char *path, char *cmd, t_pipex *data)
{
	int		status;
	char	*abs_cmd;
	char	**cmds;
	
	status = 1;
	cmds = ft_split(cmd, ' ');
	if (!cmds)
		show_error(data, "ft_split", MALLOC);
	abs_cmd = combine_path(path, cmds[0]);
	if (!abs_cmd)
	{
		free_matrix(cmds);
		show_error(data, "combine_path", MALLOC);
	}
	if (access(abs_cmd, F_OK) == 0)
	{
		if (access(abs_cmd, X_OK) == -1)
			status = -1;
		else if (execve(abs_cmd, cmds, data->ep) != -1)
			status = 0;
	}
	free_matrix(cmds);
	free(abs_cmd);
	return (status);
}

void	handle_command(t_pipex *data, char *cmd)
{
	int		i;
	int		status;
	char	*path;

	if (!cmd || cmd[0] == '\0')
		show_error(data, cmd, PERMISSION);
	i = -1;
	status = 1;
	path = check_slash(cmd);
	if (!data->path || path)
		status = exec_cmd("", cmd, data);
	while (data->path && !path && data->path[++i])
	{
		status = exec_cmd(data->path[i], cmd, data);
		if (status == 0 || status == -1)
			break ;
	}
	ft_printf("status: %d\n", status);
	if (status == 1 || status == -1)
		handle_cmd_error(status, cmd, data);
}
