/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_confirmation_connect.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:52:09 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/07/27 18:57:18 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t handshake = 0;

int check_connection_to_server
int	main(int argc, const char *argv[])
{
	if (argv < 3)
	{
		fprintf(stderr, "Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	pid_t srv = (pid_t)ft_atoi(argv[1]);
	char msg = argv[2];


}
