/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:49:05 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/28 23:02:58 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	ack_flag = 0;

void	ack_handler(int signo)
{
	if (signo == SIGUSR2)
		ack_flag = 1; // OK
	else
		ack_flag = -1; // NG
}

bool	check_connection_to_server(pid_t server_pid)
{
	int	i;

	kill(server_pid, SIGUSR1);
	sleep(2);
	i = 0;
	while (ack_flag == -1)
	{
		write(2, "Server busy. Try again later.\n", 30);
		sleep(1);
		kill(server_pid, SIGUSR1);
		sleep(1);
		i++;
	}
	if (ack_flag == 1)
	{
		write(2, "perfect! connecting server is sucess!\n", 38);
		return (true);
	}
	else if (ack_flag == 0)
	{
		write(2, "server pid maybe wrong, cannot connect.\n", 40);
	}
	return (false);
}

void	send_bits(pid_t server_pid, uint32_t val, int cnt)
{
	int		i;
	int		bit;
	char	c;

	i = 0;
	write(1, "bit: ", 5);
	while (i < cnt)
	{
		bit = (val >> i) & 1;
		if (bit == 0)
		{
			kill(server_pid, SIGUSR1);
		}
		else if (bit == 1)
		{
			kill(server_pid, SIGUSR2);
		}
		c = '0' + bit;
		write(1, &c, 1);
		ack_flag = 0;
		while (ack_flag == 0)
			pause();
		if (ack_flag < 0)
		{
			write(2, "Server NAK’d that bit!\n", 23);
			exit(1);
		}
		usleep(100);
		i++;
	}
	printf("\n");
}

bool	send_msg_length(pid_t server_pid, const char *msg)
{
	uint32_t	len;

	len = (uint32_t)ft_strlen(msg);
	send_bits(server_pid, len, 32);
	return (true);
}

bool	send_msg(pid_t server_pid, const char *msg)
{
	uint32_t	len;
	uint32_t	i;

	len = (uint32_t)ft_strlen(msg);
	i = 0;
	while (i < len)
	{
		send_bits(server_pid, (unsigned char)msg[i], 8);
		i++;
	}
	return (true);
}

bool	send_info_to_server(pid_t server_pid, const char *msg)
{
	if (check_connection_to_server(server_pid) == false)
		return (false);
	if (send_msg_length(server_pid, msg) == false)
		return (false);
	if (send_msg(server_pid, msg) == false)
		return (false);
	write(1, "every thing it's all right!\n", 28);
	return (true);
}

int	is_valid_input(int argc, char const *argv[])
{
	pid_t	server_pid;

	if (argc != 3)
	{
		write(2, "Usage: ./client <server_pid> <message>\n", 39);
		return (-1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		write(2, "Error: Invalid server PID\n", 26);
		return (-1);
	}
	return (0);
}

int	main(int argc, char const *argv[])
{
	pid_t				server_pid;
	const char			*message_str;
	struct sigaction	sa;

	if (is_valid_input(argc, argv) == -1)
		return (-1);
	server_pid = ft_atoi(argv[1]);
	message_str = argv[2];
	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = ack_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (send_info_to_server(server_pid, message_str) == false)
	{
		return (-1);
	}
	return (0);
}
