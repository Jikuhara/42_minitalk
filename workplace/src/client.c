/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:49:05 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/07 20:52:05 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int send_char(pid_t server_pid, char c)
{
	int bit;

	for (int i = 0; i < 8; i++)
	{
		bit = (c >> i) & 1;
		if (bit == 0)
		{
			if (kill(server_pid, SIGUSR1) == -1)
			{
				return (-1);
			}
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
			{
				return (-1);
			}
		}
		usleep(100);
	}
	return (0);
}

int send_string(pid_t server_pid, char *str)
{
	int i = 0;

	while (str[i])
	{
		if (send_char(server_pid, str[i]) == -1)
		{
			return (-1);
		}
		i++;
	}
	if (send_char(server_pid, '\0') == -1)
	{
		return (-1);
	}
	return (0);
}

int	send_client_pid(pid_t server_pid)
{
	pid_t client_pid;
	int bit;

	client_pid = get_pid();
	for (int i = 0; i < 32; i++)
	{
		bit = (client_pid >> i) & 1;
		if (bit == 0)
		{
			if (kill(server_pid, SIGUSR1) == -1)
			{
				return (-1);
			}
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
			{
				return (-1);
			}
		}
		usleep(100);
	}
	return (0);
}

int main(int argc, char const *argv[])
{
	pid_t server_pid;

	if (argc != 3)
	{
		printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	server_pid = atoi(argv[1]);
	if (server_pid <= 0)
	{
		printf("Error: Invalid server PID\n");
		return (1);
	}
	if (send_client_pid(server_pid) == -1)
	{
		return (-1);
	}
	if (send_string(server_pid, (char *)argv[2]) == -1)
	{
		return (-1);
	}
	return (0);
}
