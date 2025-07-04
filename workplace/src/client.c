/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:49:05 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/04 15:09:14 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minitalk.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	pid_t server_pid;

	server_pid = atoi(argv[1]);
	printf("parent PID = %i\n", server_pid);
	kill(server_pid, SIGALRM); /* なに送信したら良いか分からん。 */
	return (0);
}
