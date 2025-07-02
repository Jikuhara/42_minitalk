/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kei2003730 <kei2003730@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:45:00 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/06/30 17:35:51 by kei2003730       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_strrcmp - Compare the suffix of a string with another string
 * @str: The string to check
 * @suffix: The suffix to compare with
 * 
 * Return: 0 if str ends with suffix, otherwise the difference
 */
int	ft_strrcmp(const char *str, const char *suffix)
{
	size_t	str_len;
	size_t	suffix_len;

	if (!str || !suffix)
		return (0);
	str_len = ft_strlen(str);
	suffix_len = ft_strlen(suffix);
	if (suffix_len > str_len)
		return (-1);
	return (ft_strncmp(str + str_len - suffix_len, suffix, suffix_len));
}
