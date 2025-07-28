/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:45:40 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/07/28 22:38:19 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
#define _DEFAULT_SOURCE
# define _POSIX_C_SOURCE 200809L
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdint.h>
# define HASH_NUM 42
typedef struct s_status
{
	pid_t	client_pid;
	size_t	current_char;
	size_t	bit_count;
}			t_status;

// Client functions
int			send_char(pid_t server_pid, char c);
int			send_string(pid_t server_pid, char *str);
void		ack_handler(int signo);
bool		check_connection_to_server(pid_t server_pid);

// Server functions
// void	*signal_handler(int signal);

#endif
