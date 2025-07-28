/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:49:05 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/28 18:38:52 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// int	send_hash_num_to_server(pid_t server_pid)
// {

// }

// bool	wait_to_receive_confirmation_from_Server(void)
// {
// 	bool	confirmation;

// 	confirmation = receive_confirmation();
// 	pause();
// 	if (confirmation == false)
// 	{
// 		printf("your input server PID is wrong.\n");
// 		return (false);
// 	}
// 	else if (confirmation == true)
// 	{
// 		return (true);
// 	}
// }

// int	check_connection_to_server(pid_t server_pid)
// {
// 	send_hash_num_to_server(server_pid);
// 	sleep(1);
// 	if (wait_to_receive_confirmation_from_Server() == false)
// 	{
// 		return (false);
// 	}
// }

void	send_bits(pid_t server_pid, uint32_t val, int cnt)
{
	int	i;
	int	bit;

	i = 0;
	printf("bit: ");
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
		printf("%d", bit);
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
	return (true);
}

int	is_valid_input(int argc, char const *argv[])
{
	pid_t	server_pid;

	if (argc != 3)
	{
		printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (-1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		printf("Error: Invalid server PID\n");
		return (-1);
	}
	return (0);
}

int	main(int argc, char const *argv[])
{
	pid_t		server_pid;
	const char	*message_str;

	if (is_valid_input(argc, argv) == -1)
		return (-1);
	server_pid = ft_atoi(argv[1]);
	message_str = argv[2];
	if (send_info_to_server(server_pid, message_str) == false)
	{
		return (-1);
	}
	return (0);
}
