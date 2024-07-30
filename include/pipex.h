/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:31:55 by likong            #+#    #+#             */
/*   Updated: 2024/07/30 12:17:04 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define STDERR 2
# define STDOUT 1
# define STDIN 0

# define FAILURE 1
# define SUCCESS 0

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>

# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"

typedef enum	s_error
{
	FORK,
	ENVP,
	MALLOC,
	PIPE,
	PERMISSION,
	FILE_NAME,
	DUP2,
	DIRECTORY,
	COMMAND
}	t_error;

typedef struct	s_pipex
{
	int		ac;
	int		infile;
	int		outfile;
	char	**av;
	char	**ep;
	char	**path;
	pid_t	*pid;
	int		*fd;
}	t_pipex;

//Initial data
void	init_data(t_pipex *data, int argc, char **argv, char **envp);

//Pipex control
int		pipex(t_pipex *p);

//Tools function
int		open_file(t_pipex *data, int i);
int		check_empty(char *str);
void	free_close(t_pipex *data);
char	*check_slash(char *cmd);
int		pid_wait(pid_t pid);

//Exit part
void	show_error(t_pipex *data, char *message, t_error error);
void	success_exit(t_pipex *data);
void	free_close(t_pipex *data);
void	close_pipe(t_pipex *data);

//Handle command
void	handle_command(t_pipex *data, char *cmd);

#endif
