/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:33:59 by likong            #+#    #+#             */
/*   Updated: 2024/07/27 13:05:43 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// static void	

void	pipex(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->ac - 3)
	{
		p->pid[i] = fork();
		if (p->pid[i] < 0)
			show_error(p, NULL, FORK);
		if (p->pid[i] == 0)
			//pipex_child(p, i);
		i++;
	}
}
