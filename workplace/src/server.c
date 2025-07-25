/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:49:05 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/24 22:39:35 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "../includes/minitalk.h"
#include <unistd.h>
#include <signal.h>

t_status	status;

void	set_status(void)
{
	status.client_pid = 0;
	status.current_char = 0;
	status.bit_count = 0;
}

void signal_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (status.client_pid != info->si_pid)
		set_status();
	else if (signal == SIGUSR2)
		status.current_char |= (1 << status.bit_count);
	status.bit_count++;
	if (status.bit_count == 8)
	{
		if (status.current_char == 0)
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR2);
		}
		else
		{
			write(1, &status.current_char, 1);
		}
		set_status();
	}
	status.client_pid = info->si_pid;
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	sa = {0};
	t_status			*status;

	server_pid = getpid();
	printf("Server PID: %d\n", server_pid);
	set_status();
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
	{
		pause();
	}
	return (0);
}
