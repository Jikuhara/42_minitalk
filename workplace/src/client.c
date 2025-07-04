/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:49:05 by kei2003730        #+#    #+#             */
/*   Updated: 2025/07/04 15:54:24 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minitalk.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char const *argv[])
{
	int num;

	for (size_t i = 1; i < argc; i++)
	{
		for (size_t j = 0; j < strlen(argv[i]); j++)
		{
			num = argv[i][j];
			int bit;
			for (size_t k = 0; k < 8; k++)
			{
				bit = num & 1;
				printf("%i", bit);
				num = num >> 1;
			}
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}
