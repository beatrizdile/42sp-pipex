/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:36:11 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/05/12 15:58:52 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	c;

	c = 0;
	if (n == 0)
	{
		return (0);
	}
	while (s1[c] == s2[c] && c < (n - 1) && s1[c] != '\0' && s2[c] != '\0')
	{
		c++;
	}
	return (s1[c] - s2[c]);
}