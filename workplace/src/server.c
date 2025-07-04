/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:49:05 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/04 16:27:55 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void signal_handler(int signal)
{
	static int bit_count = 0;
	static char current_char = 0;

	if (signal == SIGUSR1)
		current_char |= (0 << bit_count);
	else if (signal == SIGUSR2)
		current_char |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		if (current_char == 0)
		{
			write(1, "\n", 1);
		}
		else
		{
			write(1, &current_char, 1);
		}
		bit_count = 0;
		current_char = 0;
	}
}

int	main(void)
{
	pid_t server_pid;

	printf("\t///////////////////////////////////////////////////\n");
	printf("\t██////██//█//██///█//█/███████///█////█/////█///█//\n");
	printf("\t██////██//█//██///█//█////█//////█////█/////█//█///\n");
	printf("\t███//█/█//█//█/█//█//█////█/////█/█///█/////█/█////\n");
	printf("\t█/█//█/█//█//█/██/█//█////█/////█/█///█/////███////\n");
	printf("\t█/█//█/█//█//█//█/█//█////█////█///█//█/////█/█////\n");
	printf("\t█//██//█//█//█///██//█////█////█████//█/////█//█///\n");
	printf("\t█//██//█//█//█///██//█////█////█///█//█/////█///█//\n");
	printf("\t█//////█//█//█////█//█////█///█/////█/█████/█///██/\n");
	printf("\t///////////////////////////////////////////////////\n");
	server_pid = getpid();
	printf("Server PID: %d\n", server_pid);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
	{
		pause();
	}
	return (0);
}
