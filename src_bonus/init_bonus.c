/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:56:24 by likong            #+#    #+#             */
/*   Updated: 2024/08/05 13:43:55 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

//Doubts here
static void init_heredoc(t_pipex *data)
{
	int		fd;
	char	*line;
	
	fd = open("here_doc", O_CREAT | O_WRONLY | O_EXCL | O_TRUNC, 0644);
	if (fd == -1)
		show_error(data, NULL, HERE_DOC, FAILSTD);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN);
		if (!line)
		{
			break ;
			// close(fd);
			// show_error(data, NULL, NEXT_LINE, FAILSTD);
		}
		if (ft_strncmp(line, data->av[2], ft_strlen(data->av[2])) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	if (!line)
		show_error(data, NULL, NEXT_LINE, FAILSTD);
	free(line);
}

static void	init_pipe(t_pipex *data)
{
	int	i;
	int	*fd;

	i = 0;
	fd = (int *)malloc(2 * (data->ac - 3 - data->here_doc) * sizeof(int));
	if (!fd)
		show_error(data, "init_pipe()", MALLOC, FAILSTD);
	while (fd && i < (data->ac - 3 - data->here_doc))
	{
		if (pipe(fd + i * 2) == -1)
		{
			i--;
			while (i >= 0)
			{
				close(fd[i * 2]);
				close(fd[i * 2 + 1]);
				i--;
			}
			free(fd);
			show_error(data, NULL, PIPE, FAILSTD);
		}
		i++;
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
	data->here_doc = 0;
	data->path = NULL;
	data->fd = NULL;
	data->pid = NULL;
	init_path(data, envp);
	init_pipe(data);
	// ft_printf("Or here, cmd: %s\n", argv[1]);
	if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		//ft_printf("Here\n");
		init_heredoc(data);
		data->here_doc = 1;
	}
	// ft_printf("here: %d\n", data->here_doc);
	data->pid = (int *)malloc((argc - 3 - data->here_doc) * sizeof(int));
	if (!data->pid)
		show_error(data, "pid", MALLOC, FAILSTD);
	// ft_printf("size: %d\n", sizeof(data->pid));
}
