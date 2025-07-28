/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:49:05 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/28 22:26:07 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "minitalk.h"

static volatile sig_atomic_t	busy = 0;
static volatile pid_t			client_pid = 0;
int								length_receiving = 1;
uint32_t						msg_len = 0;
int								len_bits = 0;
static int						bit_count = 0;
static unsigned int				char_cnt = 0;
static unsigned char			current_char = 0;

void	handle_signal(int signo, siginfo_t *info, void *ctx)
{
	pid_t	sender;
	int		bit;

	(void)ctx;
	sender = info->si_pid;
	if (!busy)
	{
		// First contact: treat any signal as a “ping”.
		busy = 1;
		client_pid = sender;
		// Send OK back:
		kill(client_pid, SIGUSR2);
		return ;
	}
	else if (sender != client_pid)
	{
		// Another client tried while busy: send NG
		kill(sender, SIGUSR1);
		return ;
	}
	// now, we'receive the msg length
	bit = (signo == SIGUSR2);
	if (length_receiving == 1)
	{
		msg_len |= ((uint32_t)bit << len_bits);
		len_bits++;
		printf("bit: %d\n", bit);
		if (len_bits == 32)
		{
			length_receiving = 0;
			printf("msg_length: %d\n", msg_len);
		}
	}
	else if (length_receiving == 0)
	{
		// receive message
		current_char |= (bit << bit_count);
		bit_count++;
		if (bit_count == 8)
		{
			write(1, &current_char, 1);
			bit_count = 0;
			current_char = 0;
			char_cnt++;
			if (char_cnt == msg_len)
			{
				busy = 0;
				client_pid = 0;
				length_receiving = 1;
				len_bits = 0;
				msg_len = 0;
				char_cnt = 0;
				write(1, "\n", 1);
			}
		}
	}
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	sa;

	server_pid = getpid();
	printf("Server PID: %d\n", server_pid);
	// set_status();
	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_sigaction = handle_signal;
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
