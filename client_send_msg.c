/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:49:05 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/28 18:06:52 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_char(pid_t server_pid, char c)
{
	int	bit;
	int	bit_count;

	bit_count = 0;
	while (bit_count < 8)
	{
		bit = (c >> bit_count) & 1;
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
		usleep(1000);
		bit_count++;
	}
	return (0);
}

void	display_end_msg(int sig)
{
	(void)sig;
	printf("every thing it's all right\n");
}

int	send_msg(pid_t server_pid, char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		if (send_char(server_pid, msg[i]) == -1)
		{
			return (-1);
		}
		i++;
	}
	if (send_char(server_pid, '\0') == -1)
	{
		return (-1);
	}
	signal(SIGUSR2, display_end_msg);
	pause();
	return (0);
}
