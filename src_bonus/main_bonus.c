/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:32:44 by likong            #+#    #+#             */
/*   Updated: 2024/08/04 12:32:46 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		status;

	if (argc < 5)
	{
		ft_printf("Correct format: \ninfile cmd1 ... cmdn outfile\n");
		return (FAILSTD);
	}
	init_data(&data, argc, argv, envp);
	status = pipex(&data);
	free_close(&data);
	return (status);
}
