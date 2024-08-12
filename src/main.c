/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:40:30 by likong            #+#    #+#             */
/*   Updated: 2024/08/12 12:04:27 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		status;

	if (argc != 5)
	{
		ft_printf("Correct format: \ninfile cmd1 cmd2 outfile\n");
		return (FAILSTD);
	}
	init_data(&data, argc, argv, envp);
	status = pipex(&data);
	free_close(&data);
	return (status);
}
