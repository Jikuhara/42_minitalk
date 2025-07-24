/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:29:29 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/07/07 20:41:05 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>

volatile sig_atomic_t	e_flag = 0;

void					abrt_handler(int sig);

int	main(void)
{
	printf("start %s\n", __func__);
	if (signal(SIGINT, abrt_handler) == SIG_ERR)
	{
		exit(1);
	}
	while (!e_flag)
	{
	}
	printf("end %s\n", __func__);
	return (0);
}

void	abrt_handler(int sig)
{
	e_flag = 1;
}
