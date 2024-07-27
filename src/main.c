/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:40:30 by likong            #+#    #+#             */
/*   Updated: 2024/07/27 13:07:54 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	int i = -1;
	while (envp[++i])
		ft_printf("%s\n", envp[i]);
	if (argc != 5)
		show_error(&data, "Correct format: \ninfile cmd1 cmd2 outfile\n", 10000);
	init_data(&data, argc, argv, envp);
	pipex(&data);
	return (0);
}

// int main(int argc, char* argv[]) {
//     int fd[2];

//     (void)argc;
//     (void)argv;
//     if (pipe(fd) == -1) {
//         return 1;
//     }
	
//     int pid1 = fork();
//     if (pid1 < 0) {
//         return 2;
//     }
	
//     if (pid1 == 0) {
//         // Child process 1 (ping)
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         execlp("ping", "ping", "-c", "1", "www.google.com", NULL);
//     }
	
//     int pid2 = fork();
//     if (pid2 < 0) {
//         return 3;
//     }
	
//     if (pid2 == 0) {
//         // Child process 2 (grep)
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         execlp("grep", "grep", "rtt", NULL);
//     }
	
//     close(fd[0]);
//     close(fd[1]);
	
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);
	
//     return 0;
// }
