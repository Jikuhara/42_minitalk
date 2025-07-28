/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_check_connection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:49:05 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/28 18:39:38 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	handshake = 0;

void	ack_handler(int signo)
{
	if (signo == SIGUSR2)
		handshake = 1; // OK
	else
		handshake = -1; // NG
}

bool	check_connection_to_server(pid_t server_pid)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = ack_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	kill(server_pid, SIGUSR1);
	sleep(2);
	int i = 0;
	while (handshake == -1)
	{
		write(2,"Server busy. Try again later.\n", 30);
		sleep(1);
		kill(server_pid, SIGUSR1);
		sleep(1);
		i++;
	}
	if (handshake == 1)
	{
		fprintf(stdout, "perfect! connecting server is sucess!\n");
		return (true);
	}
	else if (handshake == 0)
	{
		fprintf(stderr, "server pid maybe wrong, cannot connect.\n");
	}
	return (false);
}
