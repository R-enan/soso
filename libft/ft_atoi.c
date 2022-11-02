/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 06:12:30 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/07/13 16:51:28 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		n;
	char	signal;

	n = 0;
	signal = 1;
	while (nptr && *nptr >= 9 && *nptr <= 32 && *nptr != '\e')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal *= -signal;
		nptr++;
	}
	while (ft_isdigit(*nptr))
		n = n * 10 + (*nptr++ - 48);
	return (n * signal);
}
