/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:48:48 by bvelasco          #+#    #+#             */
/*   Updated: 2024/08/06 17:27:27 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint8_t	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

time_t	get_ms(void)
{
	time_t			result;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	result = tv.tv_sec * 1000;
	result += tv.tv_usec / 1000;
	return (result);
}
