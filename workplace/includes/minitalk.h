/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:45:40 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/07/24 22:27:17 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <sys/types.h>

typedef struct	s_status
{
	pid_t	client_pid;
	size_t	current_char;
	size_t	bit_count;
}			t_status;
// Client functions
int	send_char(pid_t server_pid, char c);
int	send_string(pid_t server_pid, char *str);

// Server functions
// void	*signal_handler(int signal);

#endif
