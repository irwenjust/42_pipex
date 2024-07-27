/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:31:55 by likong            #+#    #+#             */
/*   Updated: 2024/07/27 16:01:32 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define STDERR 2
# define STDOUT 1
# define STDIN 0

# include <fcntl.h>
# include <stdio.h>

# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"

typedef enum	s_error
{
	FORK,
	ENVP,
	MALLOC,
	PIPE
}	t_error;

typedef struct	s_pipex
{
	int		ac;
	int		infile;
	int		outfile;
	char	**av;
	char	**ep;
	char	**path;
	int		pid[2];
	int		fd[2];
}	t_pipex;

//Initial data
void	init_data(t_pipex *data, int argc, char **argv, char **envp);

//Pipex control
void	pipex(t_pipex *p);

//Tools function
void	show_error(t_pipex *data, char *message, t_error error);

#endif
