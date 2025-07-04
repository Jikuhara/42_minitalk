/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:49:05 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/04 19:04:02 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// int	main(int argc, char *argv[])
// {
// 	pid_t server_pid;

// 	server_pid = atoi(argv[1]);
// 	printf("parent PID = %i\n", server_pid);
// 	kill(server_pid, SIGALRM); /* なに送信したら良いか分からん。 */
// 	return (0);
// }

// int main(int argc, char const *argv[])
// {
// 	int num;

// 	for (size_t i = 0; i < argc; i++)
// 	{
// 		for (size_t j = 0; j < strlen(argv[i]); j++)
// 		{
// 			num = argv[i][j];
// 			printf("argv[%zu][%zu] = %i (%c)\n", i , j, num, argv[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	return 0;
// }

void send_char(pid_t server_pid, char c)
{
	int bit;

	for (int i = 0; i < 8; i++)
	{
		bit = (c >> i) & 1;
		if (bit == 0)
		{
			kill(server_pid, SIGUSR1);
		}
		else
		{
			kill(server_pid, SIGUSR2);
		}
		usleep(100);
	}
}

void send_string(pid_t server_pid, char *str)
{
	int i = 0;

	while (str[i])
	{
		send_char(server_pid, str[i]);
		i++;
	}
	send_char(server_pid, '\0');
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
	send_string(server_pid, (char *)argv[2]);

	return (0);
}
