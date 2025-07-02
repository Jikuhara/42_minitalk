/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:15:00 by kei2003730       #+#    #+#             */
/*   Updated: 2025/07/01 14:15:00 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs_int(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

long	ft_abs_long(long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

long long	ft_abs_long_long(long long n)
{
	if (n < 0)
		return (-n);
	return (n);
}
