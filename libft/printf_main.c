/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 08:13:25 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/07/12 17:14:04 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		str_len;
	int		count;
	int		i;

	if (!str)
		return (0);
	i = -1;
	count = 0;
	str_len = ft_strlen((char *)str);
	va_start(args, str);
	while (++i < str_len)
	{
		if (str[i] == '%')
		{
			i += 1;
			while (str[i] == '#')
				i++;
			count += convertions(str, i, args);
		}
		else
			count += ft_putchar(str[i]);
	}
	va_end(args);
	return (count);
}
